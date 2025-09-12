#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <iostream>

using namespace std;

template <typename K, typename V>
class HashTable {
public:
    explicit HashTable(size_t bucket_count = 8, float max_load_factor = 0.75f)
        : buckets_(bucket_count), count_(0), max_load_(max_load_factor) {}

    // Inserta o actualiza
    void set(const K& key, const V& value) {
        maybe_rehash();
        auto& bucket = buckets_[index_for(key)];
        for (auto& [k, v] : bucket) {
            if (k == key) { v = value; return; }
        }
        bucket.emplace_back(key, value);
        ++count_;
    }

    // Devuelve puntero a valor (o nullptr si no existe)
    V* get(const K& key) {
        auto& bucket = buckets_[index_for(key)];
        for (auto& [k, v] : bucket) if (k == key) return &v;
        return nullptr;
    }
    const V* get(const K& key) const {
        const auto& bucket = buckets_[index_for(key)];
        for (const auto& kv : bucket) if (kv.first == key) return &kv.second;
        return nullptr;
    }

    bool contains(const K& key) const { return get(key) != nullptr; }

    // Elimina, devuelve true si existía
    bool erase(const K& key) {
        auto& bucket = buckets_[index_for(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --count_;
                return true;
            }
        }
        return false;
    }

    size_t size() const { return count_; }
    bool empty() const { return count_ == 0; }

    // Nuevo método: muestra todos los elementos
    void display() const {
        cout << "{ ";
        for (const auto& bucket : buckets_) {
            for (const auto& kv : bucket) {
                cout << "(" << kv.first << ": " << kv.second << "), ";
            }
        }
        cout << "}" << endl;
    }

private:
    vector<list<pair<K,V>>> buckets_;
    size_t count_;
    float max_load_;

    size_t index_for(const K& key) const {
        return hash<K>{}(key) % buckets_.size();
    }

    void maybe_rehash() {
        if (load_factor() > max_load_) rehash(buckets_.size() * 2);
    }

    float load_factor() const {
        return buckets_.empty() ? 0.0f : static_cast<float>(count_) / buckets_.size();
    }

    void rehash(size_t new_bucket_count) {
        vector<list<pair<K,V>>> new_buckets(new_bucket_count);
        for (auto& bucket : buckets_) {
            for (auto& kv : bucket) {
                size_t idx = hash<K>{}(kv.first) % new_bucket_count;
                new_buckets[idx].push_back(move(kv));
            }
        }
        buckets_ = move(new_buckets);
    }
};

#endif // HASH_TABLE_H
