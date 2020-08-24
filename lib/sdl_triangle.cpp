#include <../include/sdl_triangle.h>

void SDL_RenderDrawTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2) {

    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x0, y0);

}

// heavily inspired by https://joshbeam.com/articles/triangle_rasterization/
void SDL_RenderFillTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2) {


    Edge edge0 = initEdge(x0, y0, x1, y1);
    Edge edge1 = initEdge(x1, y1, x2, y2);
    Edge edge2 = initEdge(x2, y2, x0, y0);
    Edge edges[3] = {edge0, edge1, edge2};

    SDL_RenderDrawEdge(renderer, edges[0]);
    SDL_RenderDrawEdge(renderer, edges[1]);
    SDL_RenderDrawEdge(renderer, edges[2]);

    // find tallest edge
    int tallestEdgeIndex = 0;
    int tallestEdgeLength = 0;
    for (int i = 0; i < 3; i++) {
        if ((edges[i].y1 - edges[i].y0) > tallestEdgeLength) {
            tallestEdgeLength = abs(edges[i].y0 - edges[i].y1);
            tallestEdgeIndex = i;
        }
    }

    // short edges
    int shortEdgeIndex_0 = (tallestEdgeIndex + 1) % 3;
    int shortEdgeIndex_1 = (tallestEdgeIndex + 2) % 3;

    DrawSpansBetweenEdges(renderer, edges[tallestEdgeIndex], edges[shortEdgeIndex_0]);
    DrawSpansBetweenEdges(renderer, edges[tallestEdgeIndex], edges[shortEdgeIndex_1]);

}

Edge initEdge(int x0, int y0, int x1, int y1) {
    Edge e;
    if (y0 < y1) {
        e.x0 = x0;
        e.y0 = y0;
        e.x1 = x1;
        e.y1 = y1;
    } else {
        e.x0 = x1;
        e.y0 = y1;
        e.x1 = x0;
        e.y1 = y0;
    }
    return e;
}

Span initSpan(int x0, int x1) {
    Span s;
    if (x0 < x1) {
        s.x0 = x0;
        s.x1 = x1;
    } else {
        s.x0 = x1;
        s.x1 = x0;
    }
    return s;
}

void SDL_RenderDrawEdge(SDL_Renderer* renderer, Edge edge) {
    SDL_RenderDrawLine(renderer, edge.x0, edge.y0, edge.x1, edge.y1);
}

void DrawSpansBetweenEdges(SDL_Renderer* renderer, Edge edge1, Edge edge2) {
    double edge1YDiff = (double) (edge1.y1 - edge1.y0);
    double edge2YDiff = (double) (edge2.y1 - edge2.y0);
    
    if (edge1YDiff == 0 || edge2YDiff == 0) {
        return;
    }

    double edge1XDiff = (double) (edge1.x1 - edge1.x0);
    double edge2XDiff = (double) (edge2.x1 - edge2.x0);
    double factor1 = (double) (edge2.y0 - edge1.y0) / edge1YDiff;
    double factorStep1 = 1.0 / edge1YDiff;
    double factor2 = 0.0;
    double factorStep2 = 1.0 / edge2YDiff;

    for(int i = edge2.y0; i < edge2.y1; i++) {
        Span span = initSpan(edge1.x0 + (int) (edge1XDiff * factor1), edge2.x0 + (int) (edge2XDiff * factor2));
        DrawSpan(renderer, span, i);
        factor1 += factorStep1;
        factor2 += factorStep2;
    }
}

void DrawSpan(SDL_Renderer* renderer, Span span, int y) {
    SDL_RenderDrawLine(renderer, span.x0, y, span.x1, y);
}