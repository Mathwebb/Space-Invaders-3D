class Vertex{
    private:
        float x, y, z;
        float normal[3];
        // float colorR, colorG, colorB;
    public:
        Vertex(){
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->normal[0] = 0;
            this->normal[1] = 0;
            this->normal[2] = 0;
        }

        Vertex(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
            this->normal[0] = 0;
            this->normal[1] = 0;
            this->normal[2] = 0;
        }

        Vertex(float posX, float posY, float posZ, float normal[3]){
            this->x = posX;
            this->y = posY;
            this->z = posZ;
            this->normal[0] = normal[0];
            this->normal[1] = normal[1];
            this->normal[2] = normal[2];
        }

        float getCoordinateX(){
            return this->x;
        }

        float getCoordinateY(){
            return this->y;
        }

        float getCoordinateZ(){
            return this->z;
        }

        float* getNormal(){
            return this->normal;
        }

        void setCoordinateX(float posX){
            this->x = posX;
        }

        void setCoordinateY(float posY){
            this->y = posY;
        }

        void setCoordinateZ(float posZ){
            this->z = posZ;
        }

        void setNormal(float normal[3]){
            this->normal[0] = normal[0];
            this->normal[1] = normal[1];
            this->normal[2] = normal[2];
        }

        void setNormal(float normalX, float normalY, float normalZ){
            this->normal[0] = normalX;
            this->normal[1] = normalY;
            this->normal[2] = normalZ;
        }
};
