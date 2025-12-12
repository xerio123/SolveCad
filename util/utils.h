//-----------------------------------------------------------------------------
// Discovery and loading of our resources (icons, fonts, templates, etc).
//
// Copyright 2016 whitequark
//-----------------------------------------------------------------------------
#include <math.h>

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <climits>
#include <cmath>
#include <csetjmp>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <functional>
#include <locale>
#include <map>
#include <memory>
#include <set>
#include <sstream>


#define EXACT(expr) (expr)

namespace SolveSpace{

    inline int WRAP(int v, int n) {
        // Clamp it to the range [0, n)
        while(v >= n) v -= n;
        while(v < 0) v += n;
        return v;
    }

    enum class StipplePattern : uint32_t {
        CONTINUOUS     = 0,
        SHORT_DASH     = 1,
        DASH           = 2,
        LONG_DASH      = 3,
        DASH_DOT       = 4,
        DASH_DOT_DOT   = 5,
        DOT            = 6,
        FREEHAND       = 7,
        ZIGZAG         = 8,

        LAST           = ZIGZAG
    };

    const std::vector<double> &StipplePatternDashes(StipplePattern pattern);
    double StipplePatternLength(StipplePattern pattern);

    std::string ssprintf(const char *fmt, ...);

    void AssertFailure(const char *file, unsigned line, const char *function,
                               const char *condition, const char *message);

    


    #define ssassert(condition, message) \
    do { \
        if(__builtin_expect((condition), true) == false) { \
            SolveSpace::AssertFailure(__FILE__, __LINE__, __func__, #condition, message); \
            __builtin_unreachable(); \
        } \
    } while(0)

    void DebugPrint(const char *fmt, ...);

    #define dbp DebugPrint
    #define DBPTRI(tri) \
    dbp("tri: (%.3f %.3f %.3f) (%.3f %.3f %.3f) (%.3f %.3f %.3f)", \
        CO((tri).a), CO((tri).b), CO((tri).c))



    // Utility functions that are provided in the platform-independent code.
    class utf8_iterator {
    const char *p, *n;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = char32_t;
        using difference_type = std::ptrdiff_t;
        using pointer = char32_t*;
        using reference = char32_t&;

        utf8_iterator(const char *p) : p(p), n(NULL) {}
        bool           operator==(const utf8_iterator &i) const { return p==i.p; }
        bool           operator!=(const utf8_iterator &i) const { return p!=i.p; }
        ptrdiff_t      operator- (const utf8_iterator &i) const { return p -i.p; }
        utf8_iterator& operator++()    { **this; p=n; n=NULL; return *this; }
        utf8_iterator  operator++(int) { utf8_iterator t(*this); operator++(); return t; }
        char32_t       operator*();
        const char*    ptr() const { return p; }
    };

    class ReadUTF8 {
        const std::string &str;
    public:
        ReadUTF8(const std::string &str) : str(str) {}
        utf8_iterator begin() const { return utf8_iterator(&str[0]); }
        utf8_iterator end()   const { return utf8_iterator(&str[0] + str.length()); }
    };


    void MakeMatrix(double *mat,
                            double a11, double a12, double a13, double a14,
                            double a21, double a22, double a23, double a24,
                            double a31, double a32, double a33, double a34,
                            double a41, double a42, double a43, double a44);

    void MultMatrix(double *mata, double *matb, double *matr);



class Vector;
class Point2d;
class Pixmap;
class Camera;
class RgbaColor;
namespace Platform {
    class Path;
} // namespace Platform

std::string LoadString(const std::string &name);
std::string LoadStringFromGzip(const std::string &name);
std::shared_ptr<Pixmap> LoadPng(const std::string &name);

class Pixmap {
public:
    enum class Format { BGRA, RGBA, BGR, RGB, A };

    Format                     format;
    size_t                     width;
    size_t                     height;
    size_t                     stride;
    std::vector<uint8_t>       data;
    int colorType;
    bool bgr;

    static std::shared_ptr<Pixmap> Create(Format format, size_t width, size_t height);
    static std::shared_ptr<Pixmap> FromPng(const uint8_t *data, size_t size, bool flip = false);

    static std::shared_ptr<Pixmap> ReadPng(FILE *f, bool flip = false);
    static std::shared_ptr<Pixmap> ReadPng(const Platform::Path &filename, bool flip = false);
    bool WritePng(FILE *f, bool flip = false);
    bool WritePng(const Platform::Path &filename, bool flip = false);

    size_t GetBytesPerPixel() const;
    RgbaColor GetPixel(size_t x, size_t y) const;
    bool Equals(const Pixmap &other) const;

    void ConvertTo(Format newFormat);
    void SetPixel(size_t x, size_t y, RgbaColor color);

    std::shared_ptr<Pixmap> Copy();
};

class BitmapFont {
public:
    struct Glyph {
        uint8_t  advanceCells;
        uint16_t position;
    };

    std::string                unifontData;
    std::map<char32_t, Glyph>  glyphs;
    std::shared_ptr<Pixmap>    texture;
    bool                       textureUpdated;
    uint16_t                   nextPosition;

    static BitmapFont From(std::string &&unifontData);
    static BitmapFont Create();

    bool IsEmpty() const { return unifontData.empty(); }
    const Glyph &GetGlyph(char32_t codepoint);
    void LocateGlyph(char32_t codepoint, double *s0, double *t0, double *s1, double *t1,
                     size_t *advanceWidth, size_t *boundingHeight);

    void AddGlyph(char32_t codepoint, std::shared_ptr<const Pixmap> pixmap);

    size_t GetWidth(char32_t codepoint);
    size_t GetWidth(const std::string &str);
};


class VectorFont {
public:
    struct Contour {
        std::vector<Point2d>   points;
    };

    struct Glyph {
        std::vector<Contour>   contours;
        double                 leftSideBearing;
        double                 boundingWidth;
        double                 advanceWidth;
    };

    std::string                lffData;
    std::map<char32_t, Glyph>  glyphs;
    double                     rightSideBearing;
    double                     capHeight;
    double                     ascender;
    double                     descender;

    static VectorFont From(std::string &&lffData);
    static VectorFont *Builtin();

    bool IsEmpty() const { return lffData.empty(); }
    const Glyph &GetGlyph(char32_t codepoint);

    double GetCapHeight(double forCapHeight) const;
    double GetHeight(double forCapHeight) const;
    double GetWidth(double forCapHeight, const std::string &str);
    Vector GetExtents(double forCapHeight, const std::string &str);

    void Trace(double forCapHeight, Vector o, Vector u, Vector v, const std::string &str,
               const std::function<void(Vector, Vector)> &traceEdge);
    void Trace(double forCapHeight, Vector o, Vector u, Vector v, const std::string &str,
               const std::function<void(Vector, Vector)> &traceEdge, const Camera &camera);
};

}

