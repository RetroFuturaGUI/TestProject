#!/usr/bin/env bash
#
# Counts lines of code across CMake, .hpp, .cpp, and shader files for the
# three project components (TestProject, RetroFuturaGUI, PlatformBridge),
# which are nested git submodules. Each component is counted excluding its
# nested submodule(s) so files aren't double-counted, plus a grand total.
#
# Usage: ./count_loc.sh [root_dir]
#   root_dir defaults to the directory containing this script.

set -euo pipefail

ROOT="${1:-$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)}"

RETROFUTURAGUI_DIR="$ROOT/RetroFuturaGUI"
PLATFORMBRIDGE_DIR="$RETROFUTURAGUI_DIR/PlatformBridge"

# File extensions considered "shader" files, plus CMake/.hpp/.cpp.
NAME_ARGS=(
    -iname "*.cmake" -o -iname "CMakeLists.txt"
    -o -iname "*.hpp" -o -iname "*.cpp"
    -o -iname "*.vs" -o -iname "*.fs" -o -iname "*.gs"
    -o -iname "*.glsl" -o -iname "*.hlsl" -o -iname "*.comp"
    -o -iname "*.vert" -o -iname "*.frag" -o -iname "*.geom"
)

# Directories to always skip (build output, VCS metadata).
PRUNE_ARGS=(-name build -o -name .git)

count_dir() {
    # $1 = directory to search
    # remaining args = directories to exclude (subtree pruned)
    local dir="$1"
    shift
    local prune=("${PRUNE_ARGS[@]}")
    for excl in "$@"; do
        prune+=(-o -path "$excl")
    done

    if [ ! -d "$dir" ]; then
        echo "0 0"
        return
    fi

    local files
    files=$(find "$dir" \( "${prune[@]}" \) -prune -o -type f \( "${NAME_ARGS[@]}" \) -print)

    local file_count=0
    local line_count=0
    if [ -n "$files" ]; then
        file_count=$(printf '%s\n' "$files" | wc -l)
        line_count=$(printf '%s\n' "$files" | xargs cat -- | wc -l)
    fi
    echo "$file_count $line_count"
}

read -r tp_files tp_lines <<< "$(count_dir "$ROOT" "$RETROFUTURAGUI_DIR")"
read -r rf_files rf_lines <<< "$(count_dir "$RETROFUTURAGUI_DIR" "$PLATFORMBRIDGE_DIR")"
read -r pb_files pb_lines <<< "$(count_dir "$PLATFORMBRIDGE_DIR")"

total_files=$((tp_files + rf_files + pb_files))
total_lines=$((tp_lines + rf_lines + pb_lines))

printf "%-20s %10s %12s\n" "Component" "Files" "Lines"
printf "%-20s %10s %12s\n" "--------------------" "----------" "------------"
printf "%-20s %10d %12d\n" "TestProject" "$tp_files" "$tp_lines"
printf "%-20s %10d %12d\n" "RetroFuturaGUI" "$rf_files" "$rf_lines"
printf "%-20s %10d %12d\n" "PlatformBridge" "$pb_files" "$pb_lines"
printf "%-20s %10s %12s\n" "--------------------" "----------" "------------"
printf "%-20s %10d %12d\n" "TOTAL" "$total_files" "$total_lines"
