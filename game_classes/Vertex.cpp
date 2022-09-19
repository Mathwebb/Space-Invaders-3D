class Vertex{
    public:
        float posX, posY, posZ;
        float normal[3];
        float colorR, colorG, colorB;
        Vertex(float posX, float posY, float posZ, float normal[3]) {
            this->posX = posX;
            this->posY = posY;
            this->posZ = posZ;
            this->normal[0] = normal[0];
            this->normal[1] = normal[1];
            this->normal[2] = normal[2];
            this->colorR = 0.0;
            this->colorG = 0.0;
            this->colorB = 0.0;
        }
        Vertex() {
            this->colorR = 0.0;
            this->colorG = 0.0;
            this->colorB = 0.0;
        }
};
