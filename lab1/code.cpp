#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
#define PB push_back
#define MP make_pair



bool prime(int n) {
    if (n < 2)
        return false;

    for (int i=2; i*i<=n; ++i)
        if (n%i == 0)
            return false;
    return true;
}



class RanGenerator
{
protected:
    int maxInt;
public:
    virtual int genInt() {
        return 0;
    }

    virtual double genReal() {
        return double(genInt())/maxInt;
    }

    vector<int> genVecInt(int n) {
        vector<int> res(n);
        for (int i=0; i<n; ++i)
            res[i] = genInt();
        return res;
    }

    vector<double> genVecReal(int n) {
        vector<double> res(n);
        for (int i=0; i<n; ++i)
            res[i] = genReal();
        return res;
    }
};  


class LCG: public RanGenerator //Linear congruential generator
{
public:
    int a,c,m,x;
    LCG(int a = 1777, int c = 7351, int m = 9973, int x = 0) {
        maxInt = m;
        this -> a = a;
        this -> c = c;
        this -> m = m;
        this -> x = x;        
    }

    int genInt() {
        return x = ((long long) a*x + c) % m;
    }
};


class SCG: public RanGenerator //Square congruential generator
{
public:
    int d,a,c,m,x;
    SCG(int d = 3889, int a = 1777, int c = 7351, int m = 9973, int x = 1) {
        maxInt = m;
        this -> d = d;          
        this -> a = a;
        this -> m = m;
        this -> c = c;
        this -> x = x;        
    }

    int genInt() {
        return x = ((long long) d*x*x + a*x + c) % m;
    }
};


class TSL: public RanGenerator //Three-sigma limits
{
public:
public:
    double m,sig;
    RanGenerator* g;

    TSL(double m, double sig) {
        this -> sig = sig;          
        this -> m = m;
        this -> g = new SCG();
    }

    int genInt() {
        return 0;
    }

    double genReal() {
        double sum = 0;
        for (int i=0; i<12; ++i)
            sum += g -> genReal();
        return m + (sum - 6)*sig;
    }
};




void drawHistogramUniform(int cnt, RanGenerator* g) {
    int n = 1000;
    vector<double> numbers = g -> genVecReal(n);
    
    vector<int> dist(cnt);
    for (double x:numbers)
        dist[floor(x*cnt)]++;

    cout << "  Interval    | Frequency\n";
    cout << fixed;
    for (int i=0; i<cnt; ++i) {
        // cout << "[" << setprecision(2) << double(i)/cnt << "; " << double(i+1)/cnt << ")  |  ";
        // cout << setprecision(5) << double(dist[i])/n << '\n';

        double l,r,v;
        l = double(i)/cnt;
        r = double(i+1)/cnt;
        v = double(dist[i])/n;        
        printf("[%.2f; %.2f)  |  %.5f\n", l, r, v);
    }

}


void drawHistogramNormal(int cnt, double l, double r, RanGenerator* g) {
    int n = 10000;
    vector<double> numbers = g -> genVecReal(n);
    
    vector<int> dist(cnt);
    for (double x:numbers) {
        if (x < l || x > r)
            continue;
        int p = (x-l) / (r-l) * cnt;
        dist[p]++;
    }
    
    cout << "   Interval     | Frequency\n";
    cout << fixed << showpos;
    for (int i=0; i<cnt; ++i) {

        double ln,rn,v;
        ln = i*(r-l)/cnt + l;
        rn = (i+1)*(r-l)/cnt + l;
        v = double(dist[i])/n;        
        printf("[%+.2f; %+.2f)  |  %.5f\n", ln, rn, v);
    }

}




int main()
{

    int type;
    // type = 6;
    cin >> type;
    
    --type;
    RanGenerator *gens[10] = {
        new LCG(1777, 7351, 9973),
        new SCG(10, 100, 30),
        nullptr,
        nullptr,
        nullptr,
        new TSL(0, 3),
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };


    if (type >= 0 && type < 5)
        drawHistogramUniform(10, gens[type]);
    
    if (type >= 5 && type < 8)
        drawHistogramNormal(12, -3, +3, gens[type]);





}


/**

9973, 9967, 9949, 9941, 9931, 9929, 9923, 9907, 9901, 9887, 9883, 9871, 9859, 9857, 9851, 9839, 9833, 9829, 9817, 9811, 9803, 9791, 9787, 9781, 9769, 9767, 9749, 9743, 9739, 9733, 9721, 9719, 9697, 9689, 9679, 9677, 9661, 9649, 9643, 9631, 9629, 9623, 9619, 9613, 9601, 9587, 9551, 9547, 9539, 9533, 9521, 9511, 9497, 9491, 9479, 9473, 9467, 9463, 9461, 9439, 9437, 9433, 9431, 9421, 9419, 9413, 9403, 9397, 9391, 9377, 9371, 9349, 9343, 9341, 9337, 9323, 9319, 9311, 9293, 9283, 9281, 9277, 9257, 9241, 9239, 9227, 9221, 9209, 9203, 9199, 9187, 9181, 9173, 9161, 9157, 9151, 9137, 9133, 9127, 9109, 9103, 9091, 9067, 9059, 9049, 9043, 9041, 9029, 9013, 9011, 9007, 9001, 8999, 8971, 8969, 8963, 8951, 8941, 8933, 8929, 8923, 8893, 8887, 8867, 8863, 8861, 8849, 8839, 8837, 8831, 8821, 8819, 8807, 8803, 8783, 8779, 8761, 8753, 8747, 8741, 8737, 8731, 8719, 8713, 8707, 8699, 8693, 8689, 8681, 8677, 8669, 8663, 8647, 8641, 8629, 8627, 8623, 8609, 8599, 8597, 8581, 8573, 8563, 8543, 8539, 8537, 8527, 8521, 8513, 8501, 8467, 8461, 8447, 8443, 8431, 8429, 8423, 8419, 8389, 8387, 8377, 8369, 8363, 8353, 8329, 8317, 8311, 8297, 8293, 8291, 8287, 8273, 8269, 8263, 8243, 8237, 8233, 8231, 8221, 8219, 8209, 8191, 8179, 8171, 8167, 8161, 8147, 8123, 8117, 8111, 8101, 8093, 8089, 8087, 8081, 8069, 8059, 8053, 8039, 8017, 8011, 8009, 7993, 7963, 7951, 7949, 7937, 7933, 7927, 7919, 7907, 7901, 7883, 7879, 7877, 7873, 7867, 7853, 7841, 7829, 7823, 7817, 7793, 7789, 7759, 7757, 7753, 7741, 7727, 7723, 7717, 7703, 7699, 7691, 7687, 7681, 7673, 7669, 7649, 7643, 7639, 7621, 7607, 7603, 7591, 7589, 7583, 7577, 7573, 7561, 7559, 7549, 7547, 7541, 7537, 7529, 7523, 7517, 7507, 7499, 7489, 7487, 7481, 7477, 7459, 7457, 7451, 7433, 7417, 7411, 7393, 7369, 7351, 7349, 7333, 7331, 7321, 7309, 7307, 7297, 7283, 7253, 7247, 7243, 7237, 7229, 7219, 7213, 7211, 7207, 7193, 7187, 7177, 7159, 7151, 7129, 7127, 7121, 7109, 7103, 7079, 7069, 7057, 7043, 7039, 7027, 7019, 7013, 7001, 6997, 6991, 6983, 6977, 6971, 6967, 6961, 6959, 6949, 6947, 6917, 6911, 6907, 6899, 6883, 6871, 6869, 6863, 6857, 6841, 6833, 6829, 6827, 6823, 6803, 6793, 6791, 6781, 6779, 6763, 6761, 6737, 6733, 6719, 6709, 6703, 6701, 6691, 6689, 6679, 6673, 6661, 6659, 6653, 6637, 6619, 6607, 6599, 6581, 6577, 6571, 6569, 6563, 6553, 6551, 6547, 6529, 6521, 6491, 6481, 6473, 6469, 6451, 6449, 6427, 6421, 6397, 6389, 6379, 6373, 6367, 6361, 6359, 6353, 6343, 6337, 6329, 6323, 6317, 6311, 6301, 6299, 6287, 6277, 6271, 6269, 6263, 6257, 6247, 6229, 6221, 6217, 6211, 6203, 6199, 6197, 6173, 6163, 6151, 6143, 6133, 6131, 6121, 6113, 6101, 6091, 6089, 6079, 6073, 6067, 6053, 6047, 6043, 6037, 6029, 6011, 6007, 5987, 5981, 5953, 5939, 5927, 5923, 5903, 5897, 5881, 5879, 5869, 5867, 5861, 5857, 5851, 5849, 5843, 5839, 5827, 5821, 5813, 5807, 5801, 5791, 5783, 5779, 5749, 5743, 5741, 5737, 5717, 5711, 5701, 5693, 5689, 5683, 5669, 5659, 5657, 5653, 5651, 5647, 5641, 5639, 5623, 5591, 5581, 5573, 5569, 5563, 5557, 5531, 5527, 5521, 5519, 5507, 5503, 5501, 5483, 5479, 5477, 5471, 5449, 5443, 5441, 5437, 5431, 5419, 5417, 5413, 5407, 5399, 5393, 5387, 5381, 5351, 5347, 5333, 5323, 5309, 5303, 5297, 5281, 5279, 5273, 5261, 5237, 5233, 5231, 5227, 5209, 5197, 5189, 5179, 5171, 5167, 5153, 5147, 5119, 5113, 5107, 5101, 5099, 5087, 5081, 5077, 5059, 5051, 5039, 5023, 5021, 5011, 5009, 5003, 4999, 4993, 4987, 4973, 4969, 4967, 4957, 4951, 4943, 4937, 4933, 4931, 4919, 4909, 4903, 4889, 4877, 4871, 4861, 4831, 4817, 4813, 4801, 4799, 4793, 4789, 4787, 4783, 4759, 4751, 4733, 4729, 4723, 4721, 4703, 4691, 4679, 4673, 4663, 4657, 4651, 4649, 4643, 4639, 4637, 4621, 4603, 4597, 4591, 4583, 4567, 4561, 4549, 4547, 4523, 4519, 4517, 4513, 4507, 4493, 4483, 4481, 4463, 4457, 4451, 4447, 4441, 4423, 4421, 4409, 4397, 4391, 4373, 4363, 4357, 4349, 4339, 4337, 4327, 4297, 4289, 4283, 4273, 4271, 4261, 4259, 4253, 4243, 4241, 4231, 4229, 4219, 4217, 4211, 4201, 4177, 4159, 4157, 4153, 4139, 4133, 4129, 4127, 4111, 4099, 4093, 4091, 4079, 4073, 4057, 4051, 4049, 4027, 4021, 4019, 4013, 4007, 4003, 4001, 3989, 3967, 3947, 3943, 3931, 3929, 3923, 3919, 3917, 3911, 3907, 3889, 3881, 3877, 3863, 3853, 3851, 3847, 3833, 3823, 3821, 3803, 3797, 3793, 3779, 3769, 3767, 3761, 3739, 3733, 3727, 3719, 3709, 3701, 3697, 3691, 3677, 3673, 3671, 3659, 3643, 3637, 3631, 3623, 3617, 3613, 3607, 3593, 3583, 3581, 3571, 3559, 3557, 3547, 3541, 3539, 3533, 3529, 3527, 3517, 3511, 3499, 3491, 3469, 3467, 3463, 3461, 3457, 3449, 3433, 3413, 3407, 3391, 3389, 3373, 3371, 3361, 3359, 3347, 3343, 3331, 3329, 3323, 3319, 3313, 3307, 3301, 3299, 3271, 3259, 3257, 3253, 3251, 3229, 3221, 3217, 3209, 3203, 3191, 3187, 3181, 3169, 3167, 3163, 3137, 3121, 3119, 3109, 3089, 3083, 3079, 3067, 3061, 3049, 3041, 3037, 3023, 3019, 3011, 3001, 2999, 2971, 2969, 2963, 2957, 2953, 2939, 2927, 2917, 2909, 2903, 2897, 2887, 2879, 2861, 2857, 2851, 2843, 2837, 2833, 2819, 2803, 2801, 2797, 2791, 2789, 2777, 2767, 2753, 2749, 2741, 2731, 2729, 2719, 2713, 2711, 2707, 2699, 2693, 2689, 2687, 2683, 2677, 2671, 2663, 2659, 2657, 2647, 2633, 2621, 2617, 2609, 2593, 2591, 2579, 2557, 2551, 2549, 2543, 2539, 2531, 2521, 2503, 2477, 2473, 2467, 2459, 2447, 2441, 2437, 2423, 2417, 2411, 2399, 2393, 2389, 2383, 2381, 2377, 2371, 2357, 2351, 2347, 2341, 2339, 2333, 2311, 2309, 2297, 2293, 2287, 2281, 2273, 2269, 2267, 2251, 2243, 2239, 2237, 2221, 2213, 2207, 2203, 2179, 2161, 2153, 2143, 2141, 2137, 2131, 2129, 2113, 2111, 2099, 2089, 2087, 2083, 2081, 2069, 2063, 2053, 2039, 2029, 2027, 2017, 2011, 2003, 1999, 1997, 1993, 1987, 1979, 1973, 1951, 1949, 1933, 1931, 1913, 1907, 1901, 1889, 1879, 1877, 1873, 1871, 1867, 1861, 1847, 1831, 1823, 1811, 1801, 1789, 1787, 1783, 1777, 1759, 1753, 1747, 1741, 1733, 1723, 1721, 1709, 1699, 1697, 1693, 1669, 1667, 1663, 1657, 1637, 1627, 1621, 1619, 1613, 1609, 1607, 1601, 1597, 1583, 1579, 1571, 1567, 1559, 1553, 1549, 1543, 1531, 1523, 1511, 1499, 1493, 1489, 1487, 1483, 1481, 1471, 1459, 1453, 1451, 1447, 1439, 1433, 1429, 1427, 1423, 1409, 1399, 1381, 1373, 1367, 1361, 1327, 1321, 1319, 1307, 1303, 1301, 1297, 1291, 1289, 1283, 1279, 1277, 1259, 1249, 1237, 1231, 1229, 1223, 1217, 1213, 1201, 1193, 1187, 1181, 1171, 1163, 1153, 1151, 1129, 1123, 1117, 1109, 1103, 1097, 1093, 1091, 1087, 1069, 1063, 1061, 1051, 1049, 1039, 1033, 1031, 1021, 1019, 1013, 1009, 997, 991, 983, 977, 971, 967, 953, 947, 941, 937, 929, 919, 911, 907, 887, 883, 881, 877, 863, 859, 857, 853, 839, 829, 827, 823, 821, 811, 809, 797, 787, 773, 769, 761, 757, 751, 743, 739, 733, 727, 719, 709, 701, 691, 683, 677, 673, 661, 659, 653, 647, 643, 641, 631, 619, 617, 613, 607, 601, 599, 593, 587, 577, 571, 569, 563, 557, 547, 541, 523, 521, 509, 503, 499, 491, 487, 479, 467, 463, 461, 457, 449, 443, 439, 433, 431, 421, 419, 409, 401, 397, 389, 383, 379, 373, 367, 359, 353, 349, 347, 337, 331, 317, 313, 311, 307, 293, 283, 281, 277, 271, 269, 263, 257, 251, 241, 239, 233, 229, 227, 223, 211, 199, 197, 193, 191, 181, 179, 173, 167, 163, 157, 151, 149, 139, 137, 131, 127, 113, 109, 107, 103, 101, 97, 89, 83, 79, 73, 71, 67, 61, 59, 53, 47, 43, 41, 37, 31, 29, 23, 19, 17, 13, 11, 7,

*/