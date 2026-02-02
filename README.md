# cc-context-watch

A status line tool that displays your Claude Code context window usage with color-coded percentage indicators.

## Installation

### Requirements
- CMake 3.14+
- C++17 compiler

### Build

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

The binary will be at `build/cc-context-watch`.

### Configure Claude Code

Add this to `~/.claude/settings.json`:

```json
{
  "statusLine": {
    "type": "command",
    "command": "/absolute/path/to/cc-context-watch",
    "padding": 0
  }
}
```

Replace `/absolute/path/to/cc-context-watch` with the actual path to your built binary.

## Usage

Once configured, cc-context-watch will automatically display your context usage in Claude Code's status line:

```
Opus | Context: 42.5% (19.8K / 200K)
```

The percentage is color-coded based on usage:
- Green: < 50%
- Yellow: 50-75%
- Red: > 75%

## License

MIT License

