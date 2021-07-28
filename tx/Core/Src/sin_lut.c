/**
  ******************************************************************************
  * @file    sin_lut.c
  * @author  yxnan@pm.me
  * @date    2021-07-27
  * @brief   采样率200kHz，深度11位的正弦查找表（仅前四分之一周期）
  ******************************************************************************
  * @attention
  *
  * C89 doesn't allow the trailing comma.
  * C99 does allow it.
  *
  ******************************************************************************
  */

#include "sin_lut.h"

dac_data_t get_lut_data(lut_index_t acc)
{
  if (acc < 512)
  {
    return sinelut_512[acc];
  }
  else if (acc == 512)
  {
    return sinelut_512[511];
  }
  else if (513 <= acc && acc <= 1024)
  {
    return sinelut_512[1024 - acc];
  }
  else if (1025 <= acc && acc <= 1535)
  {
    return 2*sinelut_512[0]-sinelut_512[acc - 1024];
  }
  else if (acc == 1536)
  {
    return 2*sinelut_512[0]-sinelut_512[511];
  }
  else if (1537 <= acc && acc <= 2047)
  {
    return 2*sinelut_512[0]-sinelut_512[2048 - acc];
  }
  else
  {
    return get_lut_data(acc % 2048);
  }
}

const dac_data_t sinelut_512[] =
{
  1986, 1990, 1994, 1997, 2001, 2005, 2009, 2013, 2016, 2020, 2024, 2028, 2032, 2035, 2039, 2043,
  2047, 2051, 2054, 2058, 2062, 2066, 2070, 2073, 2077, 2081, 2085, 2089, 2092, 2096, 2100, 2104,
  2108, 2111, 2115, 2119, 2123, 2127, 2130, 2134, 2138, 2142, 2145, 2149, 2153, 2157, 2161, 2164,
  2168, 2172, 2176, 2179, 2183, 2187, 2191, 2194, 2198, 2202, 2206, 2209, 2213, 2217, 2221, 2224,
  2228, 2232, 2236, 2239, 2243, 2247, 2250, 2254, 2258, 2262, 2265, 2269, 2273, 2276, 2280, 2284,
  2288, 2291, 2295, 2299, 2302, 2306, 2310, 2313, 2317, 2321, 2324, 2328, 2332, 2335, 2339, 2343,
  2346, 2350, 2354, 2357, 2361, 2364, 2368, 2372, 2375, 2379, 2383, 2386, 2390, 2393, 2397, 2401,
  2404, 2408, 2411, 2415, 2418, 2422, 2426, 2429, 2433, 2436, 2440, 2443, 2447, 2450, 2454, 2457,
  2461, 2464, 2468, 2471, 2475, 2478, 2482, 2485, 2489, 2492, 2496, 2499, 2503, 2506, 2510, 2513,
  2517, 2520, 2524, 2527, 2530, 2534, 2537, 2541, 2544, 2547, 2551, 2554, 2558, 2561, 2564, 2568,
  2571, 2574, 2578, 2581, 2584, 2588, 2591, 2594, 2598, 2601, 2604, 2608, 2611, 2614, 2618, 2621,
  2624, 2627, 2631, 2634, 2637, 2640, 2644, 2647, 2650, 2653, 2656, 2660, 2663, 2666, 2669, 2672,
  2676, 2679, 2682, 2685, 2688, 2691, 2694, 2698, 2701, 2704, 2707, 2710, 2713, 2716, 2719, 2722,
  2725, 2728, 2731, 2734, 2738, 2741, 2744, 2747, 2750, 2753, 2756, 2759, 2762, 2764, 2767, 2770,
  2773, 2776, 2779, 2782, 2785, 2788, 2791, 2794, 2797, 2800, 2802, 2805, 2808, 2811, 2814, 2817,
  2819, 2822, 2825, 2828, 2831, 2833, 2836, 2839, 2842, 2845, 2847, 2850, 2853, 2855, 2858, 2861,
  2864, 2866, 2869, 2872, 2874, 2877, 2880, 2882, 2885, 2888, 2890, 2893, 2895, 2898, 2900, 2903,
  2906, 2908, 2911, 2913, 2916, 2918, 2921, 2923, 2926, 2928, 2931, 2933, 2936, 2938, 2941, 2943,
  2945, 2948, 2950, 2953, 2955, 2957, 2960, 2962, 2964, 2967, 2969, 2971, 2974, 2976, 2978, 2981,
  2983, 2985, 2987, 2990, 2992, 2994, 2996, 2999, 3001, 3003, 3005, 3007, 3009, 3012, 3014, 3016,
  3018, 3020, 3022, 3024, 3026, 3028, 3030, 3033, 3035, 3037, 3039, 3041, 3043, 3045, 3047, 3049,
  3051, 3053, 3054, 3056, 3058, 3060, 3062, 3064, 3066, 3068, 3070, 3071, 3073, 3075, 3077, 3079,
  3081, 3082, 3084, 3086, 3088, 3089, 3091, 3093, 3095, 3096, 3098, 3100, 3101, 3103, 3105, 3106,
  3108, 3110, 3111, 3113, 3114, 3116, 3118, 3119, 3121, 3122, 3124, 3125, 3127, 3128, 3130, 3131,
  3133, 3134, 3136, 3137, 3138, 3140, 3141, 3143, 3144, 3145, 3147, 3148, 3149, 3151, 3152, 3153,
  3155, 3156, 3157, 3158, 3160, 3161, 3162, 3163, 3165, 3166, 3167, 3168, 3169, 3170, 3171, 3173,
  3174, 3175, 3176, 3177, 3178, 3179, 3180, 3181, 3182, 3183, 3184, 3185, 3186, 3187, 3188, 3189,
  3190, 3191, 3192, 3193, 3194, 3194, 3195, 3196, 3197, 3198, 3199, 3199, 3200, 3201, 3202, 3203,
  3203, 3204, 3205, 3205, 3206, 3207, 3208, 3208, 3209, 3210, 3210, 3211, 3211, 3212, 3213, 3213,
  3214, 3214, 3215, 3215, 3216, 3216, 3217, 3217, 3218, 3218, 3219, 3219, 3220, 3220, 3220, 3221,
  3221, 3222, 3222, 3222, 3223, 3223, 3223, 3224, 3224, 3224, 3224, 3225, 3225, 3225, 3225, 3225,
  3226, 3226, 3226, 3226, 3226, 3226, 3227, 3227, 3227, 3227, 3227, 3227, 3227, 3227, 3227, 3227,
};