const std = @import("std");

pub fn HashTable(comptime Key: type, comptime Value: type) type {
    return struct {
        const Self = @This();

        allocator: std.mem.Allocator,
        size: usize,
        buckets: std.ArrayList(std.ArrayList(Entry)),

        const Entry = struct {
            key: Key,
            value: Value,
        };

        pub fn init(allocator: std.mem.Allocator, size: usize) !Self {
            if (size == 0) return error.InvalidSize;

            var buckets = std.ArrayList(std.ArrayList(Entry)).init(allocator);
            errdefer buckets.deinit();

            for (0..size) |_| {
                try buckets.append(std.ArrayList(Entry).init(allocator));
            }

            return Self{
                .allocator = allocator,
                .size = size,
                .buckets = buckets,
            };
        }

        pub fn deinit(self: *Self) void {
            for (self.buckets.items) |*bucket| {
                bucket.deinit();
            }
            self.buckets.deinit();
        }

        fn getIndex(self: Self, key: Key) usize {
            const hash_u64 = std.hash.autoHash(key);
            return @as(usize, @intCast(hash_u64 % self.size));
        }

        pub fn remove(self: *Self, key: Key) ?Value {
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

        pub fn search(self: Self, key: Key) ?Value {
            const index = self.getIndex(key);
            const bucket = &self.buckets.items[index];

            for (bucket.items) |entry| {
                if (entry.key == key) {
                    return entry.value;
                }
            }

            return null;
        }
        pub fn insert(self: *Self, key: Key, value: Value) !void {
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

        pub fn update(self: *Self, key: Key, value: Value) !void {
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
}
