#include "builder/builder.h"
#include "Objects/compositObject.h"
#include "Objects/atomObject.h"
#include "Objects/lineObject.h"
#include "model/inc/atom.h"


//Поиск атомов с уникальными координатами
bool BaseBuilder::selectUniqueAtoms(std::vector<AtomObject> atomVect)
{
    uniqueCoords.clear();
    atoms.clear();
    for (int i = 0; i < atomVect.size(); i++)
    {
        bool is_unique = true;
        FlatCoords &curCoords = atomVect[i].coords;
        for (int j = 0; j < uniqueCoords.size() && is_unique; j++)
            is_unique &= curCoords != uniqueCoords[j];

        if (is_unique)
        {
            uniqueCoords.push_back(FlatCoords(curCoords));

            RGBColor &curColor = atomVect[i].color;
            QColor color(curColor.r, curColor.g, curColor.b);

            SpaceCoords atomCoords (curCoords.x, 0, curCoords.y);
            atomCoords.empty = 1;

            Atom obj = Atom{color, atomVect[i].radius, atomCoords};
            atoms.push_back(obj);
        }
    }
    return atoms.size() > 0;
}

//Поиск соединений между атомами по координатам концов
bool BaseBuilder::selectConnections(std::vector<LineObject> lineVect)
{
    connections.clear();
    connections = std::vector<std::vector<int>>(atoms.size(), std::vector<int>(atoms.size(), 0));

    int atomsAmount = uniqueCoords.size();
    int size = lineVect.size();
    for (int index = 0; index < size; index++)
    {
        bool found;
        FlatCoords coords;
        int i, j;

        found = false;
        coords = lineVect[index].atomStart->coords;
        for (i = 0; i < atomsAmount && found == false; i++)
            found = coords == uniqueCoords[i];

        found = false;
        coords = lineVect[index].atomEnd->coords;
        for (j = 0; j < atomsAmount && found == false; j++)
            found = coords == uniqueCoords[j];

        i--;
        j--;
        connections[i][j] = lineVect[index].linesCnt;
        connections[j][i] = lineVect[index].linesCnt;
    }
    return true;
}

//Объединение совпадающих элементов сцены
bool BaseBuilder::joinElements(const CompositObject& composit)
{
    if (this->selectUniqueAtoms(composit.getAtoms()))
    {
        this->selectConnections(composit.getLines());
        return true;
    }
    return false;
}

//Обход в ширину. Поиск отдельных структурных формул
std::vector<int> BaseBuilder::visitNode(int _node)
{
    std::vector<int> all(atoms.size());
    for (int i = 0; i < all.size(); i++)
        all[i] = i + 1;

    std::vector<int> visited;
    std::list<int> stack;

    all[_node] *= -1;
    stack.push_back(_node);
    while (stack.size())
    {
        int node = stack.back();
        stack.pop_back();
        visited.push_back(node);

        for (int i = 0; i < connections.size(); i++)
            if (connections[node][i] > 0 && all[i] > 0)
            {
                all[i] *= -1;
                stack.push_back(i);
            }
    }
    return visited;
}

//Разбиение структурной формулы на несвязные части
bool BaseBuilder::splitParts()
{
    parts.clear();

    std::vector<int> nodes(atoms.size());
    for (int i = 0; i < nodes.size(); i++)
        nodes[i] = i + 1;

    bool checked = false;
    while (checked == false)
    {
        checked = true;

        int i = 0;
        for (; i < nodes.size() && nodes[i] < 0; i++);

        if (i < nodes.size())
        {
            std::vector<int> part = this->visitNode(i);
            parts.push_back(part);
            for (int j = 0; j < part.size(); j++)
                nodes[part[j]] *= -1;
            checked = false;
        }
    }
    return true;
}
