// SPDX-License-Identifier: BSL-1.0
#pragma once

#if defined(__clang__)
#define MC_THREAD_SAFETY_ATTRIBUTE(x) __attribute__((x))
#else
#define MC_THREAD_SAFETY_ATTRIBUTE(x)
#endif

#define MC_THREAD_CAPABILITY(x) MC_THREAD_SAFETY_ATTRIBUTE(capability(x))

#define MC_THREAD_SCOPED_CAPABILITY MC_THREAD_SAFETY_ATTRIBUTE(scoped_lockable)

#define MC_THREAD_GUARDED_BY(x) MC_THREAD_SAFETY_ATTRIBUTE(guarded_by(x))

#define MC_THREAD_PT_GUARDED_BY(x) MC_THREAD_SAFETY_ATTRIBUTE(pt_guarded_by(x))

#define MC_THREAD_ACQUIRED_BEFORE(...)                                         \
    MC_THREAD_SAFETY_ATTRIBUTE(acquired_before(__VA_ARGS__))

#define MC_THREAD_ACQUIRED_AFTER(...)                                          \
    MC_THREAD_SAFETY_ATTRIBUTE(acquired_after(__VA_ARGS__))

#define MC_THREAD_REQUIRES(...)                                                \
    MC_THREAD_SAFETY_ATTRIBUTE(requires_capability(__VA_ARGS__))

#define MC_THREAD_REQUIRES_SHARED(...)                                         \
    MC_THREAD_SAFETY_ATTRIBUTE(requires_shared_capability(__VA_ARGS__))

#define MC_THREAD_ACQUIRE(...)                                                 \
    MC_THREAD_SAFETY_ATTRIBUTE(acquire_capability(__VA_ARGS__))

#define MC_THREAD_ACQUIRE_SHARED(...)                                          \
    MC_THREAD_SAFETY_ATTRIBUTE(acquire_shared_capability(__VA_ARGS__))

#define MC_THREAD_RELEASE(...)                                                 \
    MC_THREAD_SAFETY_ATTRIBUTE(release_capability(__VA_ARGS__))

#define MC_THREAD_RELEASE_SHARED(...)                                          \
    MC_THREAD_SAFETY_ATTRIBUTE(release_shared_capability(__VA_ARGS__))

#define MC_THREAD_RELEASE_GENERIC(...)                                         \
    MC_THREAD_SAFETY_ATTRIBUTE(release_generic_capability(__VA_ARGS__))

#define MC_THREAD_TRY_ACQUIRE(...)                                             \
    MC_THREAD_SAFETY_ATTRIBUTE(try_acquire_capability(__VA_ARGS__))

#define MC_THREAD_TRY_ACQUIRE_SHARED(...)                                      \
    MC_THREAD_SAFETY_ATTRIBUTE(try_acquire_shared_capability(__VA_ARGS__))

#define MC_THREAD_EXCLUDES(...)                                                \
    MC_THREAD_SAFETY_ATTRIBUTE(locks_excluded(__VA_ARGS__))

#define MC_THREAD_ASSERT_CAPABILITY(x)                                         \
    MC_THREAD_SAFETY_ATTRIBUTE(assert_capability(x))

#define MC_THREAD_ASSERT_SHARED_CAPABILITY(x)                                  \
    MC_THREAD_SAFETY_ATTRIBUTE(assert_shared_capability(x))

#define MC_THREAD_RETURN_CAPABILITY(x)                                         \
    MC_THREAD_SAFETY_ATTRIBUTE(lock_returned(x))

#define MC_THREAD_NO_SAFETY_ANALYSIS                                           \
    MC_THREAD_SAFETY_ATTRIBUTE(no_thread_safety_analysis)
