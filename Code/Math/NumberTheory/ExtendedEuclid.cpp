 Gia su ket qua la (x0. y0), ho nghiem la  (x_0 + k * b / d, y_0 - k * a/d)
 Phuong trinh ax + by = d co nghiem khi va chi khi d chia het cho gcd(a, b)
 a x + b y = gcd(a, b)
int extgcd(int a, int b, int &x, int &y) {
    int g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}