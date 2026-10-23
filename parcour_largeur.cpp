#include <iostream> 
#include <queue>// Permet d'utiliser la file (queue) pour le parcours BFS

using namespace std; 
struct Noeud {
    char valeur;      // Stocke la lettre contenue dans le nœud
    Noeud* gauche;    // Pointeur vers le fils gauche du nœud
    Noeud* droit;     // Pointeur vers le fils droit du nœud
};

// Fonction BFS : effectue un parcours en largeur de l'arbre
// R représente la racine (le premier nœud) de l'arbre
void BFS(Noeud* R) {

    // Si la racine est vide, il n'y a aucun nœud à parcourir
    if (R == nullptr)
        return; // Quitte immédiatement la fonction
    // Déclare une file qui contiendra des pointeurs vers les nœuds
    queue<Noeud*> F;
    // Ajoute la racine de l'arbre dans la file
    F.push(R);
    // Continue tant que la file n'est pas vide
    while (!F.empty()) {
        // Récupère le premier nœud de la file sans le supprimer
        Noeud* X = F.front();
        // Supprime ce nœud de la file, car il va être traité
        F.pop();
        // Affiche la valeur du nœud actuellement traité
        cout << X->valeur << " ";
        // Vérifie si le nœud possède un fils gauche
        if (X->gauche != nullptr)
            // Si oui, ajoute le fils gauche à la fin de la file
            F.push(X->gauche);
        // Vérifie si le nœud possède un fils droit
        if (X->droit != nullptr)
            // Si oui, ajoute le fils droit à la fin de la file
            F.push(X->droit);
    }
}


int main() {
    Noeud D = {'D', nullptr, nullptr};
    Noeud E = {'E', nullptr, nullptr};
    Noeud F = {'F', nullptr, nullptr};
    Noeud G = {'G', nullptr, nullptr};
    Noeud B = {'B', &D, &E};
    Noeud C = {'C', &F, &G};
    Noeud A = {'A', &B, &C};
    BFS(&A);
    return 0;
}
//VECTEUR 
/*#include <iostream>
#include <vector>
using namespace std;

struct Noeud {
    char valeur;
    Noeud* gauche;
    Noeud* droit;
};

void BFS(Noeud* R) {
    if (R == nullptr)
        return;

    vector<Noeud*> V;
    V.push_back(R);

    int i = 0;

    while (i < V.size()) {
        Noeud* X = V[i];
        cout << X->valeur << " ";
        i++;

        if (X->gauche != nullptr)
            V.push_back(X->gauche);

        if (X->droit != nullptr)
            V.push_back(X->droit);
    }
}
int main() {
    Noeud D = {'D', nullptr, nullptr};
    Noeud E = {'E', nullptr, nullptr};
    Noeud F = {'F', nullptr, nullptr};
    Noeud G = {'G', nullptr, nullptr};

    Noeud B = {'B', &D, &E};
    Noeud C = {'C', &F, &G};

    Noeud A = {'A', &B, &C};

    BFS(&A);

    return 0;
}*/