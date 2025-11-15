#include <iostream>   // 用于输入输出
#include <cmath>      // 用于数学函数（如 sqrt）
#include <memory>     // 用于智能指针 std::unique_ptr
#include <iomanip>    // 用于设置输出格式（如小数位数）

/*
程序说明（中文注释）:
该程序定义了一个几何图形的接口类 shape（抽象基类），并派生出 circle、triangle、rectangle 三个具体类。
每个具体类实现两个纯虚函数：area() 返回面积，perimeter() 返回周长。
主程序提供交互式菜单，用户可选择图形并输入对应参数，程序会校验输入有效性并输出计算结果。
*/

class shape {
public:
    // 纯虚函数：计算面积，派生类必须实现
    virtual double area() const = 0;
    // 纯虚函数：计算周长，派生类必须实现
    virtual double perimeter() const = 0;
    virtual ~shape() {} // 虚析构函数，确保通过基类指针删除派生类对象时能正确析构
};

class circle : public shape {
private:
    double radius; // 圆的半径，必须为正数
public:
    // 构造函数：接收半径并保存
    circle(double r) : radius(r) {}
    // 返回圆的面积：π * r^2
    double area() const override {
        return 3.14159265358979323846 * radius * radius;
    }
    // 返回圆的周长（周长也称为圆周长）：2 * π * r
    double perimeter() const override {
        return 2 * 3.14159265358979323846 * radius;
    }
};

class triangle : public shape {
private:
    double a, b, c; // 三角形三边长度
public:
    // 构造函数：接收三边长度
    triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {}
    // 使用海伦公式计算三角形面积：
    // s = (a + b + c) / 2
    // area = sqrt(s * (s - a) * (s - b) * (s - c))
    // 注意：在调用前应保证 a, b, c 满足三角形不等式且都为正
    double area() const override {
        double s = (a + b + c) / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    // 周长为三边之和
    double perimeter() const override {
        return a + b + c;
    }
};

class rectangle : public shape {
private:
    double length, width; // 矩形的长和宽，均应为正数
public:
    // 构造函数：接收长和宽
    rectangle(double l, double w) : length(l), width(w) {}
    // 面积 = 长 * 宽
    double area() const override {
        return length * width;
    }
    // 周长 = 2 * (长 + 宽)
    double perimeter() const override {
        return 2 * (length + width);
    }
};

// 辅助函数：检查三边是否能构成合法的三角形
// 要求三边均为正且满足三角形不等式
static bool valid_triangle(double a, double b, double c) {
    return a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a);
}

int main() {
    // 设置输出格式：固定小数，并保留两位小数，便于展示面积与周长的值
    std::cout << std::fixed << std::setprecision(2);

    // 主循环：反复显示菜单直到用户选择退出
    while (true) {
        std::cout << "\n请选择要计算的图形:\n";
        std::cout << "1 - 圆\n";
        std::cout << "2 - 三角形\n";
        std::cout << "3 - 矩形\n";
        std::cout << "0 - 退出\n";
        std::cout << "输入序号: ";
        int choice;
        // 读取用户选择；如果读取失败（如输入非数字），则清理输入流并提示重新输入
        if (!(std::cin >> choice)) {
            std::cin.clear(); // 清除错误状态
            std::cin.ignore(10000, '\n'); // 丢弃当前行剩余输入
            std::cout << "输入无效，请重试。\n";
            continue;
        }
        if (choice == 0) { // 选择退出
            break;
        }

        // 使用智能指针保存不同类型的 shape 对象，便于统一处理并自动释放资源
        std::unique_ptr<shape> shp;

        if (choice == 1) { // 圆
            double r;
            std::cout << "请输入半径: ";
            // 校验半径必须为正数，且输入为数字
            if (!(std::cin >> r) || r <= 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "半径必须为正数。\n";
                continue;
            }
            // 创建圆对象
            shp = std::make_unique<circle>(r);

        } else if (choice == 2) { // 三角形
            double a, b, c;
            std::cout << "请输入三边 a b c: ";
            // 读取三边长度，并检查输入有效性
            if (!(std::cin >> a >> b >> c)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "输入无效。\n";
                continue;
            }
            // 检查三角形合法性（正数且满足三角形不等式）
            if (!valid_triangle(a, b, c)) {
                std::cout << "三边不符合三角形不等式或非正，请重试。\n";
                continue;
            }
            // 创建三角形对象
            shp = std::make_unique<triangle>(a, b, c);

        } else if (choice == 3) { // 矩形
            double l, w;
            std::cout << "请输入长和宽: ";
            // 校验长宽为正数
            if (!(std::cin >> l >> w) || l <= 0 || w <= 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "长宽必须为正数。\n";
                continue;
            }
            // 创建矩形对象
            shp = std::make_unique<rectangle>(l, w);

        } else { // 非法选项处理
            std::cout << "未识别的选项，请重试。\n";
            continue;
        }

        // 计算并输出面积与周长；通过 shape 接口统一调用派生类实现
        std::cout << "面积: " << shp->area() << "\n";
        std::cout << "周长: " << shp->perimeter() << "\n";
    }

    std::cout << "程序结束。\n";
    return 0;
}