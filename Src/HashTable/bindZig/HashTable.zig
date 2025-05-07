const std = @import("std");

pub const HashTable_u32_u32 = struct {
    allocator: std.mem.Allocator,
    size: usize,
    buckets: std.ArrayList(std.ArrayList(Entry)),

    const Entry = struct {
        key: u32,
        value: u32,
    };

    pub fn init(allocator: std.mem.Allocator, size: usize) !*HashTable_u32_u32 {
        if (size == 0) return error.InvalidSize;
        var self = try allocator.create(HashTable_u32_u32);
        self.* = HashTable_u32_u32{
            .allocator = allocator,
            .size = size,
            .buckets = std.ArrayList(std.ArrayList(Entry)).init(allocator),
        };
        // For each bucket, initialize an empty list.
        for (0..size) |_| {
            try self.buckets.append(std.ArrayList(Entry).init(allocator));
        }
        return self;
    }

    pub fn deinit(self: *HashTable_u32_u32) void {
        for (self.buckets.items) |*bucket| {
            bucket.deinit();
        }
        self.buckets.deinit();
        self.allocator.destroy(self);
    }

    fn getIndex(self: *HashTable_u32_u32, key: u32) usize {
        // Simple hash function: key modulo table size.
        return key % self.size;
    }

    pub fn insert(self: *HashTable_u32_u32, key: u32, value: u32) !void {
        const index = self.getIndex(key);
        const bucket = &self.buckets.items[index];
        for (bucket.items) |*entry| {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        try bucket.append(.{ .key = key, .value = value });
    }

    pub fn search(self: *HashTable_u32_u32, key: u32) ?u32 {
        const index = self.getIndex(key);
        const bucket = &self.buckets.items[index];
        for (bucket.items) |entry| {
            if (entry.key == key) {
                return entry.value;
            }
        }
        return null;
    }

    pub fn remove(self: *HashTable_u32_u32, key: u32) ?u32 {
        const index = self.getIndex(key);
        const bucket = &self.buckets.items[index];
        for (bucket.items, 0..) |entry, i| {
            if (entry.key == key) {
                const removed_value = entry.value;
                _ = bucket.swapRemove(i);
                return removed_value;
            }
        }
        return null;
    }

    pub fn update(self: *HashTable_u32_u32, key: u32, value: u32) !void {
        const index = self.getIndex(key);
        const bucket = &self.buckets.items[index];
        for (bucket.items) |*entry| {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        return error.KeyNotFound;
    }
};

/// Exported C API

// Creates a new hash table using the default allocator (std.heap.page_allocator).
// Returns a non-null pointer on success, or null on error.
pub export fn create_u32_hash_table_default(size: usize) ?*HashTable_u32_u32 {
    return HashTable_u32_u32.init(std.heap.page_allocator, size) catch null;
}

// Destroys a hash table.
pub export fn destroy_u32_hash_table(table: *HashTable_u32_u32) void {
    table.deinit();
}

// Inserts a key/value pair. Returns 0 on success, 1 on error.
pub export fn insert_u32(table: *HashTable_u32_u32, key: u32, value: u32) c_int {
    _ = table.insert(key, value) catch return 1;
    return 0;
}

// Searches for a key. If found, writes the value into `result` and returns 0;
// if not found, returns 1.
pub export fn search_u32(table: *HashTable_u32_u32, key: u32, result: *u32) c_int {
    const res = table.search(key);
    if (res) |val| {
        result.* = val;
        return 0;
    } else {
        return 1;
    }
}

// Removes a key. If found, writes the removed value into `result` and returns 0;
// if not found, returns 1.
pub export fn remove_u32(table: *HashTable_u32_u32, key: u32, result: *u32) c_int {
    const res = table.remove(key);
    if (res) |val| {
        result.* = val;
        return 0;
    } else {
        return 1;
    }
}

// Updates the value for a given key. Returns 0 on success, 1 on error.
pub export fn update_u32(table: *HashTable_u32_u32, key: u32, value: u32) c_int {
    _ = table.update(key, value) catch return 1;
    return 0;
}
