#pragma once

#include "common.h"
#include <stdint.h>
// ===[ FileSystem Vtable ]===
// Platform-agnostic file system interface

typedef struct FileSystem FileSystem;

typedef struct {
    // Resolve a game-relative path to a full platform path (caller frees result)
    char* (*resolvePath)(FileSystem* fs, const char* relativePath);
    // Check if a file exists
    bool (*fileExists)(FileSystem* fs, const char* relativePath);
    // Read entire file contents into a string (caller frees result), returns nullptr if not found
    char* (*readFileText)(FileSystem* fs, const char* relativePath);
    // Write string contents to a file (creates/overwrites), returns true on success
    bool (*writeFileText)(FileSystem* fs, const char* relativePath, const char* contents);
    // Delete a file, returns true on success
    bool (*deleteFile)(FileSystem* fs, const char* relativePath);
    // Read entire file as binary data (caller frees *outData), returns true on success
    bool (*readFileBinary)(FileSystem* fs, const char* relativePath, uint8_t** outData, int32_t* outSize);
    // Write binary data to a file (creates/overwrites), returns true on success
    bool (*writeFileBinary)(FileSystem* fs, const char* relativePath, const uint8_t* data, int32_t size);
    // Begin an async-group context (e.g. a Sony save data session). Metadata only; may be no-op.
    void (*asyncGroupBegin)(FileSystem* fs, const char* name);
    // Set an option key on the current async group (e.g. "showdialog", "slottitle"). Metadata only; may be no-op.
    void (*asyncGroupOption)(FileSystem* fs, const char* key);
    // End the current async group. Returns the async request id (>= 0) or -1 if not supported.
    int32_t (*asyncGroupEnd)(FileSystem* fs);
    // Async save of a binary buffer to a file. Returns request id (>= 0) or -1 if not supported.
    int32_t (*asyncBufferSave)(FileSystem* fs, const uint8_t* data, int32_t size, const char* relativePath, int32_t offset);
    // Async load of a file into the GML buffer with id `bufferId`. Returns request id (>= 0) or -1 if not supported.
    int32_t (*asyncBufferLoad)(FileSystem* fs, int32_t bufferId, const char* relativePath, int32_t offset, int32_t maxSize);
} FileSystemVtable;

struct FileSystem {
    FileSystemVtable* vtable;
};
