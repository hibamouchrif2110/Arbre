
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// ======================================
// 1. TAS MAXIMUM AVEC VECTOR
// ======================================

class TasMax {
private:
    vector<int> tas;

public:

    // Insertion
    void inserer(int valeur) {
        tas.push_back(valeur);

        int i = tas.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (tas[i] > tas[parent]) {
                int temp = tas[i];
                tas[i] = tas[parent];
                tas[parent] = temp;

                i = parent;
            }
            else {
                break;
            }
        }
    }

    // Acces au maximum sans suppression
    int afficherMax() {
        if (tas.empty())
            return -1;

        return tas[0];
    }

    // Extraction du maximum
    int extraireMax() {
        if (tas.empty())
            return -1;

        int maximum = tas[0];

        tas[0] = tas[tas.size() - 1];
        tas.pop_back();

        int i = 0;

        while (2 * i + 1 < tas.size()) {
            int gauche = 2 * i + 1;
            int droite = 2 * i + 2;

            int plusGrand = gauche;

            if (droite < tas.size() &&
                tas[droite] > tas[gauche]) {
                plusGrand = droite;
            }

            if (tas[i] < tas[plusGrand]) {
                int temp = tas[i];
                tas[i] = tas[plusGrand];
                tas[plusGrand] = temp;

                i = plusGrand;
            }
            else {
                break;
            }
        }

        return maximum;
    }

    int taille() {
        return tas.size();
    }
};


// ======================================
// 2. PROGRAMME PRINCIPAL
// ======================================

int main() {

    srand(time(NULL));

    int n;

    cout << "Donner le nombre d'elements : ";
    cin >> n;

    if (n <= 0) {
        cout << "Le nombre doit etre positif !" << endl;
        return 1;
    }

    // Generer les memes valeurs pour les deux structures
    vector<int> valeurs;

    for (int i = 0; i < n; i++) {
        valeurs.push_back(rand() % (n * 10) + 1);
    }


    // ======================================
    // A. TAS AVEC VECTOR
    // ======================================

    TasMax t;

    cout << "\n========== TAS AVEC VECTOR ==========" << endl;

    // 1. Remplissage
    auto debut = steady_clock::now();

    for (int x : valeurs) {
        t.inserer(x);
    }

    auto fin = steady_clock::now();

    auto tempsRemplissage =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Nombre d'elements : " << t.taille() << endl;

    cout << "Temps de remplissage : "
         << tempsRemplissage << " ns" << endl;


    // 2. Acces au maximum
    debut = steady_clock::now();

    int maxVector = t.afficherMax();

    fin = steady_clock::now();

    auto tempsMaxVector =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Maximum : " << maxVector << endl;

    cout << "Temps d'acces au maximum : "
         << tempsMaxVector << " ns" << endl;


    // 3. Insertion d'une nouvelle valeur
    int nouvelleValeur;

    cout << "\nDonner une nouvelle valeur a inserer : ";
    cin >> nouvelleValeur;

    debut = steady_clock::now();

    t.inserer(nouvelleValeur);

    fin = steady_clock::now();

    auto tempsInsertionVector =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Temps d'insertion : "
         << tempsInsertionVector << " ns" << endl;


    // 4. Extraction du premier maximum
    debut = steady_clock::now();

    int premierMaxVector = t.extraireMax();

    fin = steady_clock::now();

    auto tempsPremierExtractionVector =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "\nPremier maximum extrait : "
         << premierMaxVector << endl;

    cout << "Temps d'extraction du premier maximum : "
         << tempsPremierExtractionVector << " ns" << endl;


    // 5. Extraction complete des elements restants
    debut = steady_clock::now();

    while (t.taille() > 0) {
        int extrait = t.extraireMax();
    }

    fin = steady_clock::now();

    auto tempsExtractionVector =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Temps d'extraction complete : "
         << tempsExtractionVector << " ns" << endl;

    cout << "Nombre d'elements restants : "
         << t.taille() << endl;


    // ======================================
    // B. PRIORITY_QUEUE
    // ======================================

    priority_queue<int> pq;

    cout << "\n========== PRIORITY_QUEUE ==========" << endl;

    // 1. Remplissage
    debut = steady_clock::now();

    for (int x : valeurs) {
        pq.push(x);
    }

    fin = steady_clock::now();

    auto tempsRemplissagePQ =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Nombre d'elements : " << pq.size() << endl;

    cout << "Temps de remplissage : "
         << tempsRemplissagePQ << " ns" << endl;


    // 2. Acces au maximum
    debut = steady_clock::now();

    int maxPQ = pq.top();

    fin = steady_clock::now();

    auto tempsMaxPQ =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Maximum : " << maxPQ << endl;

    cout << "Temps d'acces au maximum : "
         << tempsMaxPQ << " ns" << endl;


    // 3. Insertion de la meme nouvelle valeur
    debut = steady_clock::now();

    pq.push(nouvelleValeur);

    fin = steady_clock::now();

    auto tempsInsertionPQ =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Temps d'insertion : "
         << tempsInsertionPQ << " ns" << endl;


    // 4. Extraction du premier maximum
    debut = steady_clock::now();

    int premierMaxPQ = pq.top();
    pq.pop();

    fin = steady_clock::now();

    auto tempsPremierExtractionPQ =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "\nPremier maximum extrait : "
         << premierMaxPQ << endl;

    cout << "Temps d'extraction du premier maximum : "
         << tempsPremierExtractionPQ << " ns" << endl;


    // 5. Extraction complete des elements restants
    debut = steady_clock::now();

    while (!pq.empty()) {
        pq.pop();
    }

    fin = steady_clock::now();

    auto tempsExtractionPQ =
        duration_cast<nanoseconds>(fin - debut).count();

    cout << "Temps d'extraction complete : "
         << tempsExtractionPQ << " ns" << endl;

    cout << "Nombre d'elements restants : "
         << pq.size() << endl;


    // ======================================
    // C. COMPARAISON FINALE
    // ======================================

    cout << "\n========== COMPARAISON DES TEMPS ==========" << endl;

    cout << "\nOperation\t\tVector\t\tPriority_queue" << endl;

    cout << "Remplissage\t\t"
         << tempsRemplissage << "\t\t"
         << tempsRemplissagePQ << " ns" << endl;

    cout << "Acces maximum\t\t"
         << tempsMaxVector << "\t\t"
         << tempsMaxPQ << " ns" << endl;

    cout << "Insertion\t\t"
         << tempsInsertionVector << "\t\t"
         << tempsInsertionPQ << " ns" << endl;

    cout << "Premier extraction\t"
         << tempsPremierExtractionVector << "\t\t"
         << tempsPremierExtractionPQ << " ns" << endl;

    cout << "Extraction complete\t"
         << tempsExtractionVector << "\t\t"
         << tempsExtractionPQ << " ns" << endl;

    return 0;
}
