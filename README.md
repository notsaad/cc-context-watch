# cc-context-watch

A context window usage indicator for Claude Code's status line.

## Overview

cc-context-watch displays a visual progress bar showing your current context window usage directly in Claude Code's status line. It reads JSON from stdin (provided by Claude Code's Status Line API), parses context window stats, and outputs a styled progress bar.

**Example output:**

```
Opus | Context: [████████░░░░░░░░░░░░] 42.5% (19.8K / 200K)
```

The bar is color-coded: green (<50%), yellow (50–75%), red (>75%).

## Build

Requires CMake 3.14+ and a C++17 compiler.

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

On macOS, if Apple Clang can't find C++ headers, specify a Homebrew GCC:

```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++-15 ..
```

The binary will be at `build/cc-context-watch`.

## Install

Add the following to `~/.claude/settings.json`:

```json
{
  "statusLine": {
    "type": "command",
    "command": "/absolute/path/to/cc-context-watch",
    "padding": 0
  }
}
```

Replace `/absolute/path/to/cc-context-watch` with the actual path to the built binary.

## Tech Stack

- C++17
- nlohmann/json (fetched automatically via CMake)
