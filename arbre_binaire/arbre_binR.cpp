
#include <iostream>
#include <chrono>
#include <map>
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
Arbre* racine = new Arbre(1);

int n = 30000;
// Insertion des valeurs de 2 à n
for (int i = 2; i <= n; i++) {
    racine = racine->insertion(racine, i);
}

    // =========================================
    // 1. ABR : MESURE DU TEMPS D'AFFICHAGE
    // =========================================

    cout << "========== ABR PERSONNEL ==========" << endl;
    cout << "Valeurs : ";

    auto debut = high_resolution_clock::now();

    racine->afficher(racine);

    auto fin = high_resolution_clock::now();

    auto tempsAffichage =
        duration_cast<microseconds>(fin - debut);

    cout << "\nTemps d'affichage ABR : "
         << tempsAffichage.count()
         << " microsecondes" << endl;

    // =========================================
    // 2. ABR : RECHERCHE
    // =========================================

    int rechercheABR;

    cout << "\nDonner la valeur a rechercher : ";
    cin >> rechercheABR;

    debut = high_resolution_clock::now();

    bool trouve = racine->recherche(racine, rechercheABR);

    fin = high_resolution_clock::now();

    auto tempsRecherche =
        duration_cast<microseconds>(fin - debut);

    if (trouve)
        cout << "Valeur trouvee." << endl;
    else
        cout << "Valeur non trouvee." << endl;

    cout << "Temps de recherche ABR : "
         << tempsRecherche.count()
         << " microsecondes" << endl;

    // =========================================
    // 3. ABR : SUPPRESSION
    // =========================================

    int suppressionABR;

    cout << "\nDonner la valeur a supprimer : ";
    cin >> suppressionABR;

    debut = high_resolution_clock::now();

    racine = racine->supprimer(racine, suppressionABR);

    fin = high_resolution_clock::now();

    auto tempsSuppression =
        duration_cast<microseconds>(fin - debut);

    cout << "Temps de suppression ABR : "
         << tempsSuppression.count()
         << " microsecondes" << endl;

    cout << "\nABR apres suppression : ";

    if (racine != nullptr)
        racine->afficher(racine);

    cout << endl;


    // =========================================
    // 4. INITIALISATION DE MAP
    // =========================================

    map<int, int> m;

for (int i = 1; i <= n; i++) {
    m[i] = i;
}

    cout << "\n========== STD::MAP ==========" << endl;

    // =========================================
    // 5. MAP : AFFICHAGE
    // =========================================

    cout << "Valeurs : ";

    debut = high_resolution_clock::now();

    for (const auto& element : m)
        cout << element.first << " ";

    fin = high_resolution_clock::now();

    auto tempsAffichageMap =
        duration_cast<microseconds>(fin - debut);

    cout << "\nTemps d'affichage map : "
         << tempsAffichageMap.count()
         << " microsecondes" << endl;

    // =========================================
    // 6. MAP : RECHERCHE
    // =========================================

    debut = high_resolution_clock::now();

    bool trouveMap = (m.find(rechercheABR) != m.end());

    fin = high_resolution_clock::now();

    auto tempsRechercheMap =
        duration_cast<microseconds>(fin - debut);

    if (trouveMap)
        cout << "Valeur trouvee dans map." << endl;
    else
        cout << "Valeur non trouvee dans map." << endl;

    cout << "Temps de recherche map : "
         << tempsRechercheMap.count()
         << " microsecondes" << endl;

    // =========================================
    // 7. MAP : SUPPRESSION
    // =========================================

    debut = high_resolution_clock::now();

    m.erase(suppressionABR);

    fin = high_resolution_clock::now();

    auto tempsSuppressionMap =
        duration_cast<microseconds>(fin - debut);

    cout << "Temps de suppression map : "
         << tempsSuppressionMap.count()
         << " microsecondes" << endl;

    cout << "map apres suppression : ";

    for (const auto& element : m)
        cout << element.first << " ";

    cout << endl;


    // =========================================
    // 8. COMPARAISON DES TEMPS
    // =========================================

    cout << "\n========== TABLEAU COMPARATIF =========="
         << endl;

    cout << "Operation       ABR (us)    map (us)" << endl;

    cout << "Affichage       "
         << tempsAffichage.count() << "           "
         << tempsAffichageMap.count() << endl;

    cout << "Recherche       "
         << tempsRecherche.count() << "           "
         << tempsRechercheMap.count() << endl;

    cout << "Suppression     "
         << tempsSuppression.count() << "           "
         << tempsSuppressionMap.count() << endl;

    return 0;
}
