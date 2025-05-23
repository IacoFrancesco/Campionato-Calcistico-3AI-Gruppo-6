// Progetto n.6 Campionato Calcistico Iacoangeli, Howladar, Orti.
#include <iostream>
#include <fstream>  // per salvare e caricare i file
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time()
using namespace std;

struct Squadra {
	string nome;
	int punti = 0;
	int GF = 0; // Gol fatti
	int GS = 0; // Gol subiti
    int DR = 0;
};

// dichiarazioni funzioni:
void mescola_squadre(Squadra arr[], int n);

void selection_sort(Squadra arr[],int dim);

void array_ordinato(Squadra arr[],int dim);

void verifica_input(int dim, string tipo);

void differenza_reti(Squadra arr[], int dim);

void input(Squadra arr[], int n_squadre);

void carica_classifica(Squadra arr[], int dim);
/*---------------------------------------------------------------------------------------------------*/

int main() {
	int n_squadre;
	int n_giornate;
	
	cout<<"inserisci numero squadre: ";
	cin>>n_squadre;
	
	verifica_input(n_squadre, "squadre");
	
	cout<<"inserisci il numero delle giornate: ";
	cin>>n_giornate;
	
	verifica_input(n_giornate,"giornate");
	
	cout<<endl;
	
	Squadra arr[n_squadre];


	for (int i = 0; i < n_squadre; i++) {
			cout << "Inserisci il nome della " << i + 1 << "° Squadra: ";
			cin >> arr[i].nome;
	}


	srand(time(0));
		
	for (int j = 1; j <= n_giornate; j++) {
	    mescola_squadre(arr, n_squadre);
	    
	    cout<<endl;
	    
		cout << "GIORNATA " << j << ": "<<endl<<endl;
		input(arr, n_squadre);
	}
	
	selection_sort(arr, n_squadre);  // Prima ordino per punti (decrescente)
    differenza_reti(arr, n_squadre); // Poi sistemo quelli con stessi punti usando la differenza reti

//**************************************************************{SALVATAGGIO DATI}********************************************************************* */
    carica_classifica(arr, n_squadre);


}


               // IMPLEMENTAZIONE FUNZIONI:


// per non far capitar le stesse partite in ogni giornata:
void mescola_squadre(Squadra arr[], int n) {

	for (int i = n - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		
		Squadra a = arr[i];
		
		arr[i] = arr[j];
		arr[j] = a;
	}
}



// per ordinare l'array dei punti in ordine descrescente
void selection_sort(Squadra arr[], int dim){
    for (int j = 0; j < dim - 1; j++) {
        int max = j;
        for (int i = j + 1; i < dim; i++) {
            if (arr[i].punti > arr[max].punti) {  
                max = i;
            }
        }
        if (max != j) {
            Squadra cambio = arr[j];
            arr[j] = arr[max];
            arr[max] = cambio;
        }
    }
}





// fuonzione universale per i bug
void verifica_input(int dim, string tipo) {
    if (tipo == "squadre") {
        if (dim <= 1 || dim % 2 != 0) {
            cout << "Errore: non si può fare una partita con " << dim << " squadre." << endl;
            exit(0);
        }
    } 
    else if (tipo == "giornate") {
        
         
        if (dim <= 0) {
            cout << "Errore: non si può fare una partita con " << dim << " giornate." << endl;
            exit(0); 
        } 
        
    } 
    else if (tipo == "gol") {
        if (dim < 0) {
            cout << "Errore: Una squadra non può avere " << dim << " Gol." << endl;
            exit(0); 
        }
    }
}



// per gestire la differeza reti nella classifica 
void differenza_reti(Squadra arr[], int dim){
    for(int i=0; i<dim-1; i++){
        if(arr[i].punti == arr[i+1].punti){
            int diff_1= arr[i].GF - arr[i].GS;
            int diff_2= arr[i+1].GF - arr[i+1].GS;
            
            if(diff_2 > diff_1){
                Squadra cambio= arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=cambio;
            }
        }
    }
}



void input(Squadra arr[], int n_squadre){
    for (int y = 0; y < n_squadre; y += 2) {
			int gol1, gol2;
			cout << arr[y].nome << " vs " << arr[y+1].nome << endl;
			
			cout<<"Gol della squadra "<<arr[y].nome<<": ";
			cin>>gol1;
			
			verifica_input(gol1,"gol");
			
			cout<<"Gol della squadra "<<arr[y+1].nome<<": ";
			cin>>gol2;
			
			verifica_input(gol2, "gol");
			
			cout<<endl;
			
			arr[y].GF+=gol1;
                        arr[y].GS+=gol2;
                        arr[y+1].GF+=gol2;
                        arr[y+1].GS+=gol1;
			
			if(gol1>gol2){
			    arr[y].punti+=3;
			}
			else if(gol1<gol2){
                             arr[y+1].punti+=3;
			}
			else{
			    arr[y].punti+=1;
			    arr[y+1].punti+=1;
			}
	}
}

// per stampare la classifica finale
void carica_classifica(Squadra arr[], int dim){
	std::ofstream outFile("dati.txt");
	outFile<<"\n      ----CLASSIFICA FINALE----\n\n";
	if (outFile.is_open()) {
        for(int i=0; i<dim; i++) {
        outFile<<"Squadra: "<<arr[i].nome 
            <<" | Punti: "<<arr[i].punti 
            <<" | GF: " <<arr[i].GF 
            <<" | GS: "<<arr[i].GS
            <<" | DR: "<<arr[i].GF-arr[i].GS<<endl<<endl;
        }
    
        outFile.close();
       cout << "Dati salvati." << endl;
   }
     else {
    cout << "Errore apertura file per scrittura." << endl;
    }
}
