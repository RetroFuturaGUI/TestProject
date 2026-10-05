#include "MainScene.hpp"
#include "MainScene_p.hpp"
#include <print>
#include "AudioMetadata.hpp"
#include <format>
#include <string>
#include <type_traits>
#include <variant>

// Prints everything ReadAudioMetadata finds. The format-specific part goes through std::visit,
// which hands over whichever struct _Details holds.
static void printAudioMetadata(std::string_view path)
{
    const std::optional<RetroFuturaGUI::AudioMetadata> result = RetroFuturaGUI::ReadAudioMetadata(path);

    std::println("[Metadata] {}", path);

    if(!result)
    {
        std::println("  could not be read - missing, not audio, or a format FFmpeg can't open");
        return;
    }

    const RetroFuturaGUI::AudioMetadata& metadata = *result;

    std::println("  format    {} - container {}, codec {}, free: {}", RetroFuturaGUI::GetAudioFileFormatName(metadata._Format), metadata._Container, metadata._Codec, metadata._CodecIsFree);
    std::println("  duration  {:.3f} s, {} samples{}", metadata._Seconds, metadata._TotalSamples, metadata._DurationIsEstimate ? " (estimated from the bit rate)" : "");
    std::println("  audio     {} Hz, {} channels ({}), {}, decodes to {}, {} kbps",
        metadata._SampleRate, metadata._Channels, metadata._ChannelLayout,
        metadata._BitsPerSample > 0 ? std::format("{} bits", metadata._BitsPerSample) : std::string("no fixed bit depth"),
        metadata._SampleFormat.empty() ? std::string("nothing - FFmpeg has no decoder for it") : metadata._SampleFormat,
        metadata._BitRate / 1000);

    for(const auto& [key, value] : metadata._Tags)
        std::println("  tag       {} = {}", key, value);

    for(const RetroFuturaGUI::AudioChapter& chapter : metadata._Chapters)
        std::println("  chapter   {:.3f} s -> {:.3f} s \"{}\"", chapter._StartSeconds, chapter._EndSeconds, chapter._Title);

    if(!metadata._CoverArtCodec.empty())
        std::println("  cover     {} {}x{}, {} bytes", metadata._CoverArtCodec, metadata._CoverArtWidth, metadata._CoverArtHeight, metadata._CoverArt.size());

    if(metadata._Loop)
        std::println("  loop      samples {} -> {} (end exclusive), from the {}", metadata._Loop->_StartSample, metadata._Loop->_EndSample, metadata._Loop->_Source);

    std::visit([](const auto& details)
    {
        using Details = std::decay_t<decltype(details)>;

        if constexpr (std::is_same_v<Details, RetroFuturaGUI::WavMetadata>)
        {
            std::println("  WAV       block align {}, sampler chunk: {}, unity note {}", details._BlockAlign, details._HasSamplerChunk, details._MidiUnityNote);

            for(const RetroFuturaGUI::WavSampleLoop& loop : details._Loops)
                std::println("  WAV loop  cue {}, type {}, samples {} -> {} (inclusive), play count {}", loop._CuePointId, loop._Type, loop._StartSample, loop._EndSample, loop._PlayCount);
        }
        else if constexpr (std::is_same_v<Details, RetroFuturaGUI::FlacMetadata>)
        {
            std::println("  FLAC      block size {}..{}, frame size {}..{} bytes, audio MD5 {}", details._MinBlockSize, details._MaxBlockSize, details._MinFrameSize, details._MaxFrameSize, details._AudioMd5);
        }
        else if constexpr (std::is_same_v<Details, RetroFuturaGUI::Mp3Metadata>)
        {
            std::println("  MP3       MPEG {} {}, {}, ID3v1: {}, header {}, VBR: {}, encoder {}, delay {}, padding {}",
                details._MpegVersion, details._ChannelMode, details._Id3v2Version ? std::format("ID3v2.{}", details._Id3v2Version) : "no ID3v2",
                details._HasId3v1, details._VbrHeader.empty() ? "none" : details._VbrHeader, details._IsVbr, details._Encoder, details._EncoderDelay, details._Padding);
        }
        else if constexpr (std::is_same_v<Details, RetroFuturaGUI::OggVorbisMetadata>)
        {
            std::println("  Vorbis    vendor \"{}\", bit rate nominal {} / min {} / max {}, blocks {} and {}", details._Vendor, details._NominalBitRate, details._MinimumBitRate, details._MaximumBitRate, details._ShortBlockSize, details._LongBlockSize);
        }
        else if constexpr (std::is_same_v<Details, RetroFuturaGUI::OpusMetadata>)
        {
            std::println("  Opus      version {}, pre-skip {}, input rate {} Hz, output gain {:.2f} dB, mapping family {}", details._Version, details._PreSkip, details._InputSampleRate, details._OutputGainDb, details._ChannelMappingFamily);
        }
        else if constexpr (std::is_same_v<Details, RetroFuturaGUI::M4aMetadata>)
        {
            std::println("  M4A       brand \"{}\", profile {}, delay {}, padding {}", details._MajorBrand, details._Profile.empty() ? "-" : details._Profile, details._EncoderDelay, details._Padding);
        }
        else if constexpr (std::is_same_v<Details, RetroFuturaGUI::AdxMetadata>)
        {
            std::println("  ADX       version {}, encoding type {}, {}-byte blocks, {} bits, highpass {} Hz, encryption {}, data at {}, decodable: {}",
                details._Version, details._EncodingType, details._BlockSize, details._BitsPerSample, details._HighpassFrequency, details._EncryptionType, details._DataOffset, details._Decodable);

            if(details._HasLoopInfo)
                std::println("  ADX loop  enabled: {}, samples {} -> {}, bytes {} -> {}", details._LoopEnabled, details._LoopStartSample, details._LoopEndSample, details._LoopStartByte, details._LoopEndByte);
        }
    }, metadata._Details);
}

void TestProject::MainScene::testAudioMetadata()
{
    // One file per format - paste real ones over the placeholders. A path that doesn't exist just
    // reports that it couldn't be read.
    constexpr std::string_view paths[]
    {
        R"(C:\Users\Sophie\kDrive\Music\電気グルーヴ\人間と動物\06 Prof. Radio.flac)",
        R"(C:\Users\Sophie\Music\相対性理論\天声ジングル\相対性理論 - ケルベロス.mp3)",
        R"(C:\Windows\Media\Alarm01.wav)",
        R"(C:\Program Files (x86)\Steam\steamui\sounds\steam_at_mention.m4a)",
        R"(C:\path\to\test.ogg)",
        R"(C:\path\to\test.opus)",
        R"(C:\Users\Sophie\Music\mutecity.adx)",
        R"(C:\Users\Sophie\Music\falcon_14.ahx)",
    };

    for(const std::string_view path : paths)
        printAudioMetadata(path);
}

void TestProject::MainScene::on_testButton_clicked()
{
    //static bool checkRef = false;
    std::println("testButton Clicked!");
    //testAudioMetadata();
    //glm::vec3 currentRotation = _members->_testModel->GetRotation();
    //_members->_testModel->SetRotation(currentRotation += glm::vec3(4.0f, 6.0f, 7.0f));
    //_members->_testCheckBox->SetInheritValueReference(&checkRef);
    //_members->_testCheckBox->UseInherietedValue(true);
    _members->_testTextBox->SetValue<f64>(0.33333333333333333333333333333333333333333333333333333333333333333333, false);
    _members->_testTable->SetValue<f64>(0.33333333333333333333333333333333333333333333333333333333333333333333, { ._Row = 0, ._Column = 0 }, false);

    // first click opens and plays, every click after that pauses or carries on
    static bool opened { false };
    static bool playing { false };

    if(!opened)
    {
        opened = _members->_testVideo->OpenVideoFile(R"(C:\Users\Sophie\Videos\test.webm)");
        std::println("video open: {}", opened);

        if(!opened)
            return;
    }

    if(playing)
        _members->_testVideo->Pause();
    else
        _members->_testVideo->Play();

    playing = !playing;

}

void TestProject::MainScene::on_testTextBox_textChange()
{
    /*static std::string valueStr;
    valueStr =  _members->_testTextBox->GetText();
    std::println("testTextBox current Text: {}", valueStr);

    if(valueStr.empty())
        return;

    static u32 value;

    static bool validNumber;
    validNumber = true;

    for (char c : valueStr)
    {
        if (!isdigit(c))
        {
            validNumber = false;
            break;
        }
    }

    if(!validNumber)
        return;
    
    value = std::stoi(valueStr);
    _members->_testSlider->SetValue<u32>(value, false);*/

    std::println("bool: {}\ni8: {}\ni16: {}\ni32: {}\ni64: {}\nu8: {}\nu16: {}\nu32: {}\nu64: {}\nf32: {}\nf64: {}", 
        _members->_testTextBox->GetValue<bool>(),
        _members->_testTextBox->GetValue<i8>(),
        _members->_testTextBox->GetValue<i16>(),
        _members->_testTextBox->GetValue<i32>(),
        _members->_testTextBox->GetValue<i64>(),
        _members->_testTextBox->GetValue<u8>(),
        _members->_testTextBox->GetValue<u16>(),
        _members->_testTextBox->GetValue<u32>(),
        _members->_testTextBox->GetValue<u64>(),
        _members->_testTextBox->GetValue<f32>(),
        _members->_testTextBox->GetValue<f64>()
    );
}

void TestProject::MainScene::on_testTableTextChange()
{
    std::println("bool: {}\ni8: {}\ni16: {}\ni32: {}\ni64: {}\nu8: {}\nu16: {}\nu32: {}\nu64: {}\nf32: {}\nf64: {}", 
        _members->_testTable->GetValue<bool>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<i8>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<i16>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<i32>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<i64>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<u8>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<u16>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<u32>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<u64>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<f32>({ ._Row = 0, ._Column = 0 }),
        _members->_testTable->GetValue<f64>({ ._Row = 0, ._Column = 0 })
    );
}

void TestProject::MainScene::on_testTextBox_enterPressed()
{
    std::println("Enter Pressed");
}

void TestProject::MainScene::on_testTextBox_enterReleased()
{
    std::println("Enter Released");
}

void TestProject::MainScene::on_testTextBox_copy()
{
    std::println("Text copied: {}", _members->_testTextBox->GetCopiedText());
}

void TestProject::MainScene::on_testTextBox_paste()
{
    std::println("Text pasted:");
}

void TestProject::MainScene::on_testSlider_valueChanged()
{
/*    static std::string _valueStr;
    static u32 value;
    value = _members->_testSlider->GetValue<u32>();
    _valueStr = std::to_string(value);
    _members->_testTextBox->SetText(_valueStr, false);
    _members->_testProgressBar->SetValue<u32>(value, false);

*/
    _members->_testTable->SetVerticalScrollPosition(_members->_testSlider->GetValue<f32>());
}

void TestProject::MainScene::on_scene_update()
{
    _members->_testProgressBar->SetValue<f32>(_members->_testVideo->GetChannelVolume(0), false);
}
