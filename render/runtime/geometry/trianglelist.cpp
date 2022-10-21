#include "trianglelist.h"

krender::TriangleList::TriangleList() {
    trianglelist.reserve(100);
};
void krender::TriangleList::AddTriangle(Triangle* triangle) {
    trianglelist.push_back(triangle);
}