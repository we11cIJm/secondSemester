#include <iostream>
#include <cmath>

namespace geo2d::orto {
    class Quad {
    protected:
        double x_{0}, y_{0}, height_{0}, width_{0};
    public:
        Quad() : x_{0}, y_{0}, height_{0}, width_{0} {}
        Quad(double x, double y, double height, double width)
            : x_{x}, y_{y}, height_{height}, width_{width}
        {}
        Quad(const Quad& other)
            : x_{other.x_}, y_{other.y_}
            , height_{other.height_}, width_{other.width_}
        {}
        ~Quad() {}

        Quad* operator=(const Quad& other) {
            x_ = other.x_;
            y_ = other.y_;
            height_ = other.height_;
            width_ = other.width_;
            return this;
        }

        virtual void Scale (double factor) = 0;
        virtual Quad* Intersect (const Quad& first, const Quad& second) const = 0;
        // virtual Quad* Union (const Quad& first, const Quad& second) const = 0;

        double GetX() const {return x_;}
        double GetY() const {return y_;}
        double GetHeight() const {return height_;}
        double GetWidth() const {return width_;}

    };

    class Rect : public Quad {
    public:
        Rect() : Quad() {}
        Rect(double x, double y, double height, double width)
            : Quad(x, y, height, width)
        {}
        
        void Scale (double factor) override {
            if (factor < 0) {
                throw std::invalid_argument("");
            }
            height_ *= factor;
            width_ *= factor;
        }

        Quad* Intersect (const Quad& first, const Quad& second) const override {
            // const Rect* r1 = dynamic_cast<const Rect*>(&first);
            // const Rect* r2 = dynamic_cast<const Rect*>(&second);
            double new_x = 0.0, new_y = 0.0, new_height = 0.0, new_width = 0.0;
            new_height =
                (first.GetHeight() + second.GetHeight()) / 2 - std::abs(first.GetY() - second.GetY());
            if (new_height < 0) {
                return nullptr;
            }
            new_width =
                (first.GetWidth() + second.GetWidth()) / 2 - std::abs(first.GetX() - second.GetX());
            double k1 = -1.0, k2 = -1.0;
            if (first.GetX() < second.GetX()) {k1 = 1;}
            if (first.GetY() > second.GetY()) {k2 = 1;}
            new_x = first.GetX() + k1 * (first.GetWidth() - new_width) / 2;
            new_y = first.GetY() + k2 * (first.GetHeight() - new_height) / 2;
            return new Rect(new_x, new_y, new_height, new_width);
        }

            /*Quad* Union(const Quad& first, const Quad& second) const override {
                // const Rect* r1 = dynamic_cast<const Rect*>(&first);
                // const Rect* r2 = dynamic_cast<const Rect*>(&second);
                if (r1 == nullptr || r2 == nullptr) { return nullptr; }
                double new_x = (x_ + r1->x_) / 2;
                double new_y = (y_ + r1->y_) / 2;
                double new_height
                    = (height_ / 2 + r->height_ / 2 + std::abs(r->x_ - x_));
                double new_width
                    = (width_ / 2 + r->width_ / 2 + std::abs(r->y_ - y_));
                return new Rect(new_x, new_y, new_height, new_width);
            };*/

    /*class Square : public Rect {
        Square() : Rect() {}
        Square(double x, double y, double height, double width = 0)
            : Rect(x, y, height, height)
        {}*/
    };

} // namespace geo2d::orto

int main(int argc, char* argv[]) {
    geo2d::orto::Rect a(1, 2, 3, 4);
    geo2d::orto::Rect b(a);

}