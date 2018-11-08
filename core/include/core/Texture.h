//
// Created by Rafik on 08.11.2018.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

class Texture
{
private:
    unsigned int m_ID;
public:
    Texture(const std::string& path, bool transparency = false);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
};

#endif //TEXTURE_H
