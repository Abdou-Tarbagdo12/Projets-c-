#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Etudiant {
public:
    string nom;
    string identifiant;
    vector<pair<string, float>> matieres;  // Pair de matière et note

    Etudiant(string n, string id) : nom(n), identifiant(id) {}

    void ajouterMatiere(const string& matiere, float note) {
        matieres.push_back({matiere, note});
    }

    void afficherNotes() {
        cout << "Notes de " << nom << " (" << identifiant << "):\n";
        for (auto& m : matieres) {
            cout << "Matière: " << m.first << " - Note: " << m.second << endl;
        }
    }

    void modifierNote(const string& matiere, float nouvelleNote) {
        for (auto& m : matieres) {
            if (m.first == matiere) {
                m.second = nouvelleNote;
                cout << "Note de " << matiere << " modifiée à " << nouvelleNote << endl;
                return;
            }
        }
        cout << "Matière non trouvée.\n";
    }

    void supprimerNote(const string& matiere) {
        for (auto it = matieres.begin(); it != matieres.end(); ++it) {
            if (it->first == matiere) {
                matieres.erase(it);
                cout << "Note de " << matiere << " supprimée.\n";
                return;
            }
        }
        cout << "Matière non trouvée.\n";
    }
};

class GestionNotes {
private:
    vector<Etudiant> etudiants;

public:
    void ajouterEtudiant(const string& nom, const string& identifiant) {
        etudiants.push_back(Etudiant(nom, identifiant));
        cout << "Étudiant " << nom << " ajouté avec succès.\n";
    }

    Etudiant* trouverEtudiant(const string& identifiant) {
        for (auto& etudiant : etudiants) {
            if (etudiant.identifiant == identifiant) {
                return &etudiant;
            }
        }
        return nullptr;
    }

    void afficherTousLesEtudiants() {
        for (auto& etudiant : etudiants) {
            etudiant.afficherNotes();
        }
    }
};

int main() {
    GestionNotes gestion;
    int choix;

    do {
        cout << "\nMenu:\n";
        cout << "1. Ajouter un étudiant\n";
        cout << "2. Ajouter des notes pour un étudiant\n";
        cout << "3. Modifier une note\n";
        cout << "4. Supprimer une note\n";
        cout << "5. Afficher les notes de tous les étudiants\n";
        cout << "0. Quitter\n";
        cout << "Votre choix: ";
        cin >> choix;
        cin.ignore();  // Pour ignorer le '\n' laissé par cin >> choix

        if (choix == 1) {
            string nom, identifiant;
            cout << "Nom de l'étudiant: ";
            getline(cin, nom);
            cout << "Identifiant de l'étudiant: ";
            getline(cin, identifiant);
            gestion.ajouterEtudiant(nom, identifiant);
        } else if (choix == 2) {
            string identifiant, matiere;
            float note;
            cout << "Identifiant de l'étudiant: ";
            getline(cin, identifiant);
            Etudiant* etudiant = gestion.trouverEtudiant(identifiant);
            if (etudiant) {
                cout << "Matière: ";
                getline(cin, matiere);
                cout << "Note: ";
                cin >> note;
                etudiant->ajouterMatiere(matiere, note);
            } else {
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choix == 3) {
            string identifiant, matiere;
            float nouvelleNote;
            cout << "Identifiant de l'étudiant: ";
            getline(cin, identifiant);
            Etudiant* etudiant = gestion.trouverEtudiant(identifiant);
            if (etudiant) {
                cout << "Matière à modifier: ";
                getline(cin, matiere);
                cout << "Nouvelle note: ";
                cin >> nouvelleNote;
                etudiant->modifierNote(matiere, nouvelleNote);
            } else {
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choix == 4) {
            string identifiant, matiere;
            cout << "Identifiant de l'étudiant: ";
            getline(cin, identifiant);
            Etudiant* etudiant = gestion.trouverEtudiant(identifiant);
            if (etudiant) {
                cout << "Matière à supprimer: ";
                getline(cin, matiere);
                etudiant->supprimerNote(matiere);
            } else {
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choix == 5) {
            gestion.afficherTousLesEtudiants();
        }

    } while (choix != 0);

    cout << "Au revoir !\n";
    return 0;
}
