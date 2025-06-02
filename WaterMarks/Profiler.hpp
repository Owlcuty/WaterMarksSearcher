#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>

// =============================================
//  Класс для удобного профилирования
// =============================================
class Profiler {
public:
    struct ProfileResult {
        std::string name;
        long long duration; // в микросекундах (us)
    };

    static void Start(const std::string& name) {
        m_profiles.push_back({ name, 0 });
        m_startTime = std::chrono::high_resolution_clock::now();
    }

    static void End() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTime).count();
        m_profiles.back().duration = duration;
    }

    static void PrintResults() {
        std::cout << "\n=== Results of profiling ===\n";
        for (const auto& profile : m_profiles) {
            std::cout << "[" << profile.name << "] " << profile.duration << " us\n";
        }
        std::cout << "================================\n";
        Clear();
    }

    static void Clear() {
        m_profiles.clear();
    }

private:
    static inline std::vector<ProfileResult> m_profiles;
    static inline std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
};

// =============================================
//  Макросы для удобного использования
// =============================================
#define PROFILE_START(name) Profiler::Start(name)
#define PROFILE_END() Profiler::End()
#define PROFILE_PRINT() Profiler::PrintResults()
#define PROFILE_SCOPE(name) ProfileScopeTimer __profile_scope__(name)

// Автоматически завершает профилирование при выходе из блока
class ProfileScopeTimer {
public:
    ProfileScopeTimer(const std::string& name) : m_name(name) {
        Profiler::Start(name);
    }
    ~ProfileScopeTimer() {
        Profiler::End();
    }
private:
    std::string m_name;
};
