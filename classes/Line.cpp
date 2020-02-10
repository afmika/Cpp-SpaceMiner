#include "Line.h"

int intersectSegment(sf::Vector2f A, sf::Vector2f B, sf::Vector2f I, sf::Vector2f P) {
	sf::Vector2f D(B.x - A.x, B.y - A.y), E(P.x - I.x, P.y - I.y);
	float d = D.x * E.y - D.y * E.x;
	if (d == 0) {
		return -1; 
	}
	float t = - (A.x*E.y - I.x * E.y - E.x * A.y + E.x * I.y) / d;
	float u = - (- D.x * A.y + D.x * I.y + D.y * A.x - D.y * I.x) / d;
	if ( t < 0 || t >= 1 || u < 0 || u >= 1) {
		return 0;
	}
	return 1;
}
bool pointIsInside(vector<sf::Vector2f> points, sf::Vector2f P) {
    size_t size = points.size();
    sf::Vector2f max_point(-1, -1);
    for (size_t i = 0; i < size; i++) {
        sf::Vector2f p = points[i];
        max_point.x = max(p.x, max_point.x);
        max_point.y = max(p.y, max_point.y);
    }    
    max_point += sf::Vector2f(0, 10); // just to be sure we re outside

    int nb_intersec = 0;
    for(size_t i = 0 ; i < size; i++) {
        sf::Vector2f A = points[i];
        sf::Vector2f B = points[(i + 1) % size];
        int val = intersectSegment(A, B, max_point, P);
        if (val == 1) {
            nb_intersec++;
        }
    }
    return nb_intersec % 2 == 1;
}

Line::Line() {
    this->color = new sf::Color(0xffffff);
    this->life = 100;
}

void Line::add(sf::Vector2f point) {
    if( !this->isClosed() ) {
        this->points.push_back(point);
    }
}

bool Line::isClosed() const {
    size_t size = this->points.size();
    if(size >= 4) {
        // The two latest points only matter
        size_t lastIndex = this->points.size()-1;
        sf::Vector2f _a = this->points[lastIndex - 1];
        sf::Vector2f _b = this->points[lastIndex];

        for (size_t i = 0; i < lastIndex - 2; i++) {
            sf::Vector2f a = this->points[ i ];
            sf::Vector2f b = this->points[i + 1];
            if( intersectSegment(a, b, _a, _b) == 1) {
                return true;
            }
        }
    }
    return false;
}

bool Line::captures(Orbusoid orbus) const {
    if(this->isClosed()) {
        return pointIsInside(this->points, sf::Vector2f(orbus.x, orbus.y));
    }
    return false;
}

void Line::drawLineBetween(sf::Vector2f a, sf::Vector2f b, sf::RenderWindow &window) {
    sf::VertexArray line(sf::Lines, 2);
    line[0] = a; line[0].color = *this->color;
    line[1] = b; line[1].color = *this->color;
    window.draw(line);
}

void Line::drawInside(sf::RenderWindow &window) {
    if(this->life > 0) {
        size_t size = this->points.size();
        sf::VertexArray vertices(sf::TrianglesFan, size);
        for (size_t i = 0; i < size; i++) {
            // outline
            sf::Vector2f a = this->points[ i ];
            if(i + 1 < size) {
                sf::Vector2f b = this->points[i + 1];
                this->drawLineBetween(a, b, window);
            }
            // fill
            sf::Color temp_color = *this->color;
            temp_color.a = 100;
            vertices[i] = a; 
            vertices[i].color = temp_color;
        }
        window.draw(vertices);
    }
}

Line::~Line() {
    
}