#ifndef MODEL_H
#define MODEL_H

#include "utils.h";

std::vector<std::string> _Models;

void process_model(std::string r_path)
{
    // Load all models and get its textures paths to add them to the _Textures vector
}

void process_models()
{
    for (size_t i = 0; i < _Models.size(); i++)
    {
        process_model(_Models[i]);
    }
}

#endif // !MODEL_H
