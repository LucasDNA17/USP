#include <cmath>
#include <iostream>
#include <tuple>
#include <queue>
#include <map>


using namespace std;


//Raio médio da Terra em km
#define R_terra 6371


double graus_para_radianos(double angulo)
{
    return angulo*M_PI/180;
}


double distancia_Haversine(double latitude1, double latitude2 , double delta_longitude)
{
    double delta_latitude = latitude1 - latitude2;
    double argumento_arcsin = pow((sin(delta_latitude/2)), 2);
    argumento_arcsin += cos(latitude1)*cos(latitude2)*pow((sin(delta_longitude/2)), 2);
    argumento_arcsin = sqrt(argumento_arcsin);

    return 2*R_terra*asin(argumento_arcsin);
}


priority_queue<tuple<double, string>, vector<tuple<double, string>>, greater<>> get_palpites(int n_jogadores, double latitude, double longitude)
{
    priority_queue<tuple<double, string>, vector<tuple<double, string>>, greater<>> palpites;

    for(int i = 0; i < n_jogadores; i++)
    {
        string nome;
        double latitude_palpite;
        double longitude_palpite;
        cin >> nome;
        cin >> latitude_palpite;
        cin >> longitude_palpite;

        latitude_palpite = graus_para_radianos(latitude_palpite);
        longitude_palpite = graus_para_radianos(longitude_palpite);

        tuple<double, string> palpite(distancia_Haversine(latitude, latitude_palpite, longitude - longitude_palpite), nome);
        palpites.push(palpite); 

        tuple<double, string> melhor_palpite = palpites.top();
        printf("> [AVISO] MELHOR PALPITE: %.3lfkm\n", get<0>(melhor_palpite));
    }


    return palpites;
}


void print_palpites(priority_queue<tuple<double, string>, vector<tuple<double, string>>, greater<>> palpites)
{
    cout << "\nRANKING\n" << "-------" << endl;
    int contador = 1;
    while(!palpites.empty())
    {
        tuple<double, string> palpite = palpites.top();
        palpites.pop();

        string nome = get<1>(palpite);
        double distancia = get<0>(palpite);
        printf("%2d. %-20s : %6.3lf km", contador, nome.c_str() , distancia);

        if(distancia < 0.05)
        {
            printf(" [FANTASTICO]");
        }

        printf("\n");

        contador++;
    }
}


int main()
{
    int n_jogadores;
    cin >> n_jogadores;

    double latitude, longitude;
    cin >> latitude;
    cin >> longitude;

    latitude = graus_para_radianos(latitude);
    longitude = graus_para_radianos(longitude);

    priority_queue<tuple<double, string>, vector<tuple<double, string>>, greater<>> palpites = get_palpites(n_jogadores, latitude, longitude);
    print_palpites(palpites);

    return 0;
}