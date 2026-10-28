
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Arbre {
private:
    int valeur;
    Arbre* gauche;
    Arbre* droit;

public:
    // Constructeur
    Arbre(int x) {
        valeur = x;
        gauche = nullptr;
        droit = nullptr;
    }

    // Insertion
    Arbre* insertion(Arbre* n, int x) {
        if (n == nullptr)
            return new Arbre(x);

        if (x < n->valeur)
            n->gauche = insertion(n->gauche, x);
        else if (x > n->valeur)
            n->droit = insertion(n->droit, x);

        return n;
    }

    // Recherche
    bool recherche(Arbre* n, int x) {
        if (n == nullptr)
            return false;

        if (x == n->valeur)
            return true;
        else if (x < n->valeur)
            return recherche(n->gauche, x);
        else
            return recherche(n->droit, x);
    }

    // Suppression
    Arbre* supprimer(Arbre* n, int x) {
        if (n == nullptr)
            return nullptr;

        if (x < n->valeur) {
            n->gauche = supprimer(n->gauche, x);
        }
        else if (x > n->valeur) {
            n->droit = supprimer(n->droit, x);
        }
        else {
            // Cas 1 : aucun fils
            if (n->gauche == nullptr &&
                n->droit == nullptr) {
                delete n;
                return nullptr;
            }

            // Cas 2 : un seul fils à droite
            if (n->gauche == nullptr) {
                Arbre* temp = n->droit;
                delete n;
                return temp;
            }

            // Cas 2 : un seul fils à gauche
            if (n->droit == nullptr) {
                Arbre* temp = n->gauche;
                delete n;
                return temp;
            }

            // Cas 3 : deux fils
            Arbre* temp = n->droit;

            while (temp->gauche != nullptr)
                temp = temp->gauche;

            n->valeur = temp->valeur;
            n->droit = supprimer(n->droit, temp->valeur);
        }

        return n;
    }

    // Affichage
    void afficher(Arbre* n) {
        if (n != nullptr) {
            afficher(n->gauche);
            cout << n->valeur << " ";
            afficher(n->droit);
        }
    }
};

int main() {
    Arbre* racine = new Arbre(8);

    // Insertion des valeurs
    racine = racine->insertion(racine, 2);
    racine = racine->insertion(racine, 3);
    racine = racine->insertion(racine, 5);
    racine = racine->insertion(racine, 6);
    racine = racine->insertion(racine, 7);
    racine = racine->insertion(racine, 9);
    racine = racine->insertion(racine, 8);
    racine = racine->insertion(racine, 1);
    racine = racine->insertion(racine, 4);

    // Mesure du temps d'affichage
    auto debut = high_resolution_clock::now();

    racine->afficher(racine);

    auto fin = high_resolution_clock::now();

    auto tempsAffichage =
        duration_cast<microseconds>(fin - debut);

    cout << "\nTemps d'affichage : "
         << tempsAffichage.count()
         << " microsecondes" << endl;

    // Recherche d'une valeur
    int x;
    cout << "\nDonner la valeur a rechercher : ";
    cin >> x;

    debut = high_resolution_clock::now();

    bool trouve = racine->recherche(racine, x);

    fin = high_resolution_clock::now();

    auto tempsRecherche =
        duration_cast<microseconds>(fin - debut);

    if (trouve)
        cout << "Valeur trouvee." << endl;
    else
        cout << "Valeur non trouvee." << endl;

    cout << "Temps de recherche : "
         << tempsRecherche.count()
         << " microsecondes" << endl;

    // Suppression d'une valeur
    cout << "\nDonner la valeur a supprimer : ";
    cin >> x;

    debut = high_resolution_clock::now();

    racine = racine->supprimer(racine, x);

    fin = high_resolution_clock::now();

    auto tempsSuppression =
        duration_cast<microseconds>(fin - debut);

    cout << "Temps de suppression : "
         << tempsSuppression.count()
         << " microsecondes" << endl;

    // Affichage après suppression
    cout << "\nABR apres suppression : ";

    racine->afficher(racine);
    cout << endl;

    return 0;
}
