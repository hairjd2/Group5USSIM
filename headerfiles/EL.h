#ifndef EL_h
#define EL_h

int scanData[1000] = {
2261,
2263,
2209,
2354,
2184,
2284,
2260,
2302,
2164,
2357,
2227,
2242,
2258,
2330,
2169,
2290,
2316,
2195,
2254,
2322,
2250,
2155,
2421,
2168,
2254,
2251,
2416,
1983,
2491,
2195,
2266,
2083,
2690,
1804,
2429,
2379,
2331,
1392,
4095,
0,
4058,
1495,
2146,
2607,
2234,
1912,
2661,
2089,
2238,
2240,
2463,
1970,
2454,
2219,
2267,
2157,
2452,
2103,
2302,
2285,
2280,
2163,
2363,
2239,
2207,
2307,
2279,
2212,
2262,
2330,
2176,
2297,
2269,
2269,
2195,
2356,
2197,
2273,
2257,
2305,
2180,
2326,
2245,
2250,
2248,
2310,
2211,
2269,
2288,
2240,
2248,
2287,
2262,
2221,
2307,
2243,
2254,
2255,
2301,
2204,
2297,
2255,
2264,
2230,
2312,
2221,
2269,
2267,
2271,
2227,
2293,
2256,
2242,
2273,
2272,
2242,
2259,
2288,
2230,
2271,
2266,
2266,
2230,
2301,
2237,
2264,
2257,
2284,
2223,
2289,
2255,
2257,
2251,
2287,
2237,
2263,
2274,
2253,
2251,
2275,
2263,
2239,
2283,
2254,
2256,
2256,
2285,
2230,
2278,
2259,
2264,
2241,
2291,
2239,
2264,
2263,
2270,
2239,
2279,
2260,
2250,
2265,
2270,
2249,
2258,
2278,
2244,
2264,
2265,
2265,
2240,
2285,
2247,
2262,
2257,
2278,
2236,
2277,
2258,
2259,
2252,
2280,
2246,
2261,
2269,
2258,
2252,
2270,
2263,
2246,
2274,
2259,
2257,
2256,
2278,
2240,
2271,
2260,
2264,
2245,
2282,
2247,
2262,
2261,
2269,
2244,
2273,
2261,
2254,
2262,
2269,
2252,
2258,
2274,
2250,
2261,
2264,
2265,
2245,
2278,
2253,
2261,
2257,
2275,
2242,
2272,
2260,
2260,
2252,
2276,
2250,
2260,
2267,
2260,
2253,
2268,
2264,
2249,
2269,
2261,
2258,
2256,
2275,
2246,
2267,
2261,
2264,
2247,
2277,
2251,
2261,
2260,
2269,
2247,
2270,
2262,
2256,
2260,
2268,
2254,
2257,
2271,
2254,
2260,
2263,
2265,
2248,
2273,
2256,
2260,
2257,
2273,
2246,
2268,
2260,
2261,
2253,
2273,
2253,
2259,
2265,
2262,
2253,
2266,
2264,
2252,
2266,
2262,
2258,
2256,
2272,
2250,
2265,
2261,
2265,
2249,
2274,
2254,
2261,
2260,
2269,
2249,
2267,
2262,
2257,
2259,
2268,
2256,
2257,
2269,
2256,
2259,
2263,
2265,
2250,
2270,
2258,
2260,
2257,
2271,
2249,
2266,
2261,
2262,
2253,
2271,
2255,
2259,
2263,
2263,
2254,
2265,
2264,
2253,
2264,
2263,
2259,
2256,
2271,
2252,
2263,
2261,
2265,
2250,
2271,
2256,
2260,
2259,
2268,
2251,
2266,
2262,
2258,
2258,
2267,
2257,
2257,
2267,
2258,
2258,
2262,
2265,
2251,
2268,
2259,
2260,
2256,
2270,
2251,
2265,
2261,
2263,
2253,
2270,
2256,
2259,
2262,
2264,
2254,
2264,
2264,
2255,
2263,
2263,
2259,
2256,
2269,
2254,
2262,
2261,
2265,
2251,
2269,
2257,
2260,
2258,
2268,
2252,
2264,
2262,
2259,
2257,
2267,
2258,
2257,
2266,
2259,
2258,
2262,
2265,
2253,
2266,
2260,
2261,
2256,
2269,
2253,
2263,
2261,
2263,
2253,
2268,
2257,
2259,
2261,
2264,
2255,
2263,
2264,
2256,
2261,
2263,
2260,
2256,
2268,
2256,
2261,
2261,
2265,
2252,
2268,
2258,
2261,
2258,
2268,
2253,
2263,
2262,
2260,
2257,
2266,
2259,
2258,
2265,
2260,
2258,
2261,
2265,
2254,
2265,
2260,
2261,
2256,
2269,
2254,
2263,
2261,
2264,
2254,
2267,
2258,
2259,
2261,
2265,
2255,
2262,
2264,
2257,
2261,
2263,
2260,
2256,
2267,
2257,
2261,
2260,
2265,
2253,
2267,
2259,
2261,
2258,
2267,
2254,
2263,
2262,
2261,
2257,
2266,
2259,
2258,
2264,
2261,
2258,
2261,
2265,
2255,
2264,
2261,
2261,
2256,
2268,
2255,
2262,
2260,
2264,
2254,
2266,
2259,
2260,
2260,
2265,
2256,
2262,
2263,
2258,
2260,
2263,
2261,
2256,
2266,
2258,
2260,
2260,
2265,
2254,
2265,
2260,
2261,
2257,
2267,
2255,
2262,
2262,
2262,
2256,
2265,
2260,
2258,
2263,
2262,
2258,
2261,
2265,
2256,
2263,
2261,
2261,
2256,
2267,
2256,
2261,
2260,
2264,
2254,
2266,
2259,
2260,
2259,
2265,
2256,
2261,
2263,
2259,
2259,
2263,
2261,
2257,
2265,
2259,
2260,
2260,
2265,
2254,
2264,
2260,
2261,
2257,
2267,
2256,
2262,
2261,
2262,
2256,
2265,
2260,
2258,
2262,
2262,
2258,
2260,
2265,
2256,
2262,
2261,
2262,
2256,
2266,
2257,
2261,
2260,
2264,
2255,
2265,
2260,
2260,
2259,
2265,
2257,
2261,
2263,
2259,
2259,
2263,
2261,
2257,
2264,
2260,
2260,
2260,
2265,
2255,
2264,
2260,
2261,
2257,
2266,
2257,
2261,
2261,
2263,
2256,
2264,
2261,
2258,
2261,
2263,
2258,
2260,
2264,
2257,
2261,
2261,
2262,
2256,
2266,
2258,
2261,
2260,
2265,
2255,
2264,
2260,
2260,
2259,
2265,
2257,
2261,
2263,
2260,
2259,
2263,
2261,
2257,
2264,
2260,
2260,
2259,
2265,
2256,
2263,
2261,
2262,
2257,
2266,
2257,
2261,
2261,
2263,
2256,
2264,
2261,
2259,
2261,
2263,
2259,
2260,
2264,
2258,
2261,
2261,
2262,
2256,
2265,
2259,
2261,
2260,
2265,
2256,
2264,
2260,
2261,
2258,
2265,
2258,
2260,
2262,
2261,
2258,
2263,
2262,
2257,
2263,
2261,
2260,
2259,
2265,
2256,
2262,
2261,
2262,
2257,
2266,
2258,
2261,
2260,
2263,
2256,
2263,
2261,
2259,
2260,
2263,
2259,
2259,
2264,
2258,
2260,
2261,
2262,
2256,
2265,
2259,
2261,
2259,
2265,
2256,
2263,
2261,
2261,
2258,
2265,
2258,
2260,
2262,
2261,
2258,
2262,
2262,
2258,
2262,
2261,
2260,
2259,
2265,
2257,
2262,
2261,
2262,
2257,
2265,
2258,
2261,
2260,
2263,
2257,
2263,
2261,
2259,
2260,
2263,
2259,
2259,
2263,
2259,
2260,
2261,
2262,
2257,
2264,
2260,
2261,
2259,
2265,
2256,
2263,
2261,
2261,
2258,
2265,
2259,
2260,
2262,
2262,
2258,
2262,
2262,
2258,
2262,
2261,
2260,
2259,
2264,
2257,
2261,
2261,
2262,
2257,
2265,
2259,
2261,
2260,
2264,
2257,
2262,
2261,
2260,
2259,
2263,
2259,
2259,
2263,
2260,
2260,
2261,
2263,
2257,
2263,
2260,
2261,
2259,
2265,
2257,
2262,
2261,
2262,
2257,
2264,
2259,
2260,
2261,
2262,
2258,
2262,
2262,
2258,
2261,
2262,
2260,
2259,
2264,
2258,
2261,
2261,
2263,
2257,
2264,
2259,
2261,
2260,
2264,
2257,
2262,
2261,
2260,
2259,
2263,
2260,
2259,
2263,
2260,
2260,
2261,
2263,
2257,
2263,
2260,
2261,
2259,
2265,
2257,
2262,
2261,
2262,
2257,
2264,
2259,
2260,
2261,
2262,
2258,
2262,
2262,
2259,
2261,
2262,
2260,
2259,
2264,
2259,
2261,
2261,
2263,
2257,
2264,
2260,
2261,
2259,
2264,
2257,
2262,
2261,
2260,
2259,
2263,
2260,
2259,
2262,
2261,
2259,
2261,
2263,
2257,
2262,
2261,
2261,
2258,
2264,
2258,
2261,
2261,
2262,
2257,
2264,
2260,
2260,
2261,
2263,
2258,
2261,
2262,
2259,
2261,
2262,
2260,
2258,
2264,
2259,
2261,
2260,
2263,
2257,
2263,
2260,
2261,
2259,
2264,
2258,
2261,
2261,
2261,
2259,
2263,
2260,
2259,
2262,
2261,
2259,
2261,
2263,
2258,
2262,
2261,
2261,
2258,
2264,
2258,
2261,
2261,
2262,
};

#endif