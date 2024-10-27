#include "Mocs/Dialog.moc"
#include <algorithm>
#include <queue>

Dialog::Dialog (QWidget *parent):
    QDialog {parent} 
{
    this->setFixedSize(900, 900);
}

void Dialog::appendCity (City *city) {
    connect (city, &City::cityClick, this, &Dialog::cityClicked);
    this->cities.push_back(city);
}

void Dialog::appendRoad (Road *road) {
    this->roads.push_back(road);
}

City *Dialog::findCity (std::string cityName) const {
    for (auto city : this->cities) {
        if (city->getName() == cityName) {
            return city;
        }
    } return nullptr;
}

void Dialog::raiseCities (void) {
    for (City * city : this->cities) {
        city->raise();
    }
}

void Dialog::generateRoute (void) {

    for (auto road : roads) {
        road->toggleColor(true);
    }
    for (auto city : cities) {
        if (city != fstCity && city != sndCity) {
            city->bgColor = Qt::black;
            city->textColor = Qt::white;
        }
    }

    auto route = this->getShortestRoute();

    for (size_t i{}; i < route.size(); i++) {
        if (i == route.size() -1) {
           break;
        }
        Road *road = findRoad(route[i]->getName(), route[i+1]->getName());
        road->toggleColor();
    }

    for (auto city : route) {
        if (city != route.front() && city != route.back()) {
             city->toggleColors(true);
        }
    }
    
}

std::vector<City*> Dialog::getShortestRoute() {
    std::vector<std::string> visited; // armazena cidades já visitadas
    std::vector<std::vector<City*>> routes; // armazena todas as rotas possíveis em construção
    std::vector<std::vector<City*>> validRoutes; // armazena rotas validas (fstcity primeira e sndcity ultima)

    City* node = fstCity;  // cidade inicial
    visited.push_back(node->getName()); // marca cidade inicial como visitada
    routes.push_back({node}); // adiciona a rota inicial com a cidade inicial

    while (!routes.empty()) {
        auto currentRoute = routes.front(); // pega a primeira rota da lista
        routes.erase(routes.begin()); // remove a rota da lista
        node = currentRoute.back(); // define 'node' como a última cidade da rota atual

        // se a última cidade da rota é a cidade destino, armazena a rota completa em validRoutes
        if (node == sndCity) {
            validRoutes.push_back(currentRoute);  // armazena a rota como uma rota completa para sndCity
            continue; // continua explorando outras rotas
        }

        auto neighbors = node->getNeighbors(); // obtem os vizinhos do nó atual
        for (auto neighbor : neighbors) {
            // verifica se o vizinho já foi visitado nesta rota
            if (std::find(visited.begin(), visited.end(), neighbor->getName()) == visited.end()) {
                std::vector<City*> newRoute = currentRoute; // cria uma nova rota baseada na rota atual
                newRoute.push_back(neighbor);  // adiciona o vizinho à nova rota
                routes.push_back(newRoute); // adiciona a nova rota à lista de rotas a explorar
            }
        }

        // marca o nó atual como visitado ao final do loop de vizinhos
        visited.push_back(node->getName());
    }

    std::vector<std::vector<int>> distances;
    for (auto route : validRoutes) {
        qDebug() << "rota";
        for (auto city : route) {
            qDebug() << city->getName();
        }
        std::vector<int> routeDistance;
        for (size_t i{}; i < route.size(); i++) {
            if (i == route.size() -1) {
                break;
            }
            Road *road = findRoad(route[i]->getName(), route[i+1]->getName());
            qDebug() << "#" << road->getDistance();
            routeDistance.push_back(road->getDistance());
        }

        qDebug() << "distancia da rota" << std::accumulate(routeDistance.begin(), routeDistance.end(), 0);
        qDebug() << "";

        distances.push_back(routeDistance);
    }

    auto minIt = std::min_element(distances.begin(), distances.end(),
        [](const std::vector<int>& a, const std::vector<int>& b) {
            int sumA = std::accumulate(a.begin(), a.end(), 0);
            int sumB = std::accumulate(b.begin(), b.end(), 0);
            return sumA < sumB;
        }
    );

    int minIndex = std::distance(distances.begin(), minIt);

    return validRoutes[minIndex];
}

Road *Dialog::findRoad (std::string cityStartName, std::string cityEndName) {
    for (auto road : roads) {
        if ((road->getStartCity()->getName() == cityStartName && road->getEndCity()->getName() == cityEndName) ||
            (road->getStartCity()->getName() == cityEndName && road->getEndCity()->getName() == cityStartName)) 
        {
            return road;
        }
    } return nullptr;
}

void Dialog::cityClicked (City *city) {
    if (fstCity == city) {
        fstCity = nullptr;
        return;
    }

    if (sndCity == city) {
        sndCity = nullptr;
        return;
    }

    if (fstCity == nullptr && sndCity == nullptr) {
        fstCity = city;
        return;
    } else if (fstCity == nullptr && sndCity != nullptr) {
        fstCity = sndCity;
        sndCity = city;
    } else if (fstCity != nullptr && sndCity == nullptr) {
        sndCity = city;
    } else { // ambos sao diferente de nullptr
        fstCity->toggleColors();
        fstCity = sndCity;
        sndCity = city;
    }

    generateRoute();

}