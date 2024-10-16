#ifndef FIGURE_HPP
#define FIGURE_HPP

class Figure{
private:
    /* data */
public:
    Figure(/* args */);
    ~Figure();
    virtual bool intersect() = 0;
};

Figure::Figure(/* args */){
}

Figure::~Figure(){
}


#endif /* FIGURE_HPP */