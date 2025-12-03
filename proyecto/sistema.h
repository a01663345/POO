#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include "vuelo.h"
#include "usuario.h"
#include "reservacion.h"
using namespace std;

class Sistema {
private:
    Vuelo vuelos[10];
    Usuario usuarios[10];
    Reservacion reservaciones[10];

    int numVuelos = 0;
    int numUsuarios = 0;
    int numReservaciones = 0;

public:

void menu() {
        int opcion;

        do {
            cout << "\n=================\n";
            cout << "Menu ViajandoAndo\n";
            cout << "=================\n";
            cout << "1) Dar de alta vuelo\n";
            cout << "2) Mostrar vuelos\n";
            cout << "3) Buscar vuelo por fecha\n"; // <--- NUEVA OPCION
            cout << "4) Dar de alta usuario\n";
            cout << "5) Mostrar usuarios\n";
            cout << "6) Realizar reservacion\n";
            cout << "7) Imprime reservaciones\n";
            cout << "8) Cancelar reservacion\n";
            cout << "9) Salir\n";
            cout << "\n";
            cout << "Elije una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1: 
                    agregarVuelo(); 
                break;
                case 2:
                     mostrarVuelos(); 
                break;
                case 3:
                     buscarVueloPorFecha(); // <--- LLAMADA A LA NUEVA FUNCION
                break;
                case 4: 
                    agregarUsuario(); 
                break;
                case 5: 
                    mostrarUsuarios(); 
                break;
                case 6: 
                    realizarReservacion(); 
                break;
                case 7: 
                    mostrarReservaciones(); 
                break;
                case 8: 
                    cancelarReservacion(); 
                break;
                case 9: 
                    cout << "Saliendo...\n" << endl;
                break;
                default: 
                    cout << "Opcion invalida.\n" << endl;
                break;
            }

        } while (opcion != 9); // <--- OJO: AHORA EL LIMITE ES 9
    }

    // ------------------------------
    // AGREGAR VUELO
    // ------------------------------
    void agregarVuelo() {
        if (numVuelos == 10) {
            cout << "No se pueden agregar mas vuelos.\n";
            return;
        }

        string num, aer, fecha;
        float precio;
        int dur, km;

        cout << "Numero de vuelo: ";
        cin >> num;
        cout << "Aerolinea: ";
        cin >> aer;
        cout << "Fecha: ";
        cin >> fecha;
        cout << "Precio: ";
        cin >> precio;
        cout << "Duracion (min): ";
        cin >> dur;
        cout << "Distancia (km): ";
        cin >> km;

        vuelos[numVuelos++] = Vuelo(num, aer, fecha, precio, dur, km);

        cout << "Vuelo agregado correctamente.\n";
    }

    // ------------------------------
    void mostrarVuelos() {
        if (numVuelos == 0) {
            cout << "No hay vuelos registrados.\n";
            return;
        }

        for (int i = 0; i < numVuelos; i++) {
            cout << i << ") " << vuelos[i].getNumeroVuelo()
                 << " - " << vuelos[i].getAerolinea()
                 << " - $" << vuelos[i].getPrecio()
                 << " - " << vuelos[i].getFecha()
                 << "\n";
        }
    }

    // ------------------------------
    // AGREGAR USUARIO
    // ------------------------------
    void agregarUsuario() {
        if (numUsuarios == 10) {
            cout << "No se pueden agregar mas usuarios.\n";
            return;
        }

        string id, nombre;
        cout << "ID del usuario: ";
        cin >> id;
        cout << "Nombre: ";
        cin >> nombre;

        usuarios[numUsuarios++] = Usuario(id, nombre);

        cout << "Usuario agregado correctamente.\n";
    }

    // ------------------------------
    void mostrarUsuarios() {
        if (numUsuarios == 0) {
            cout << "No hay usuarios registrados.\n";
            return;
        }

        for (int i = 0; i < numUsuarios; i++) {
            cout << i << ") " << usuarios[i].getNombre()
                 << " - ID: " << usuarios[i].getId()
                 << " - KM acumulados: " << usuarios[i].getKmAcumulados()
                 << "\n";
        }
    }

    // ------------------------------
    // REALIZAR RESERVACION
    // ------------------------------
    void realizarReservacion() {
        if (numReservaciones == 10) {
            cout << "No se pueden agregar mas reservaciones.\n";
            return;
        }

        mostrarUsuarios();
        cout << "Elige usuario: ";
        int iu;
        cin >> iu;

        mostrarVuelos();
        cout << "Elige vuelo: ";
        int iv;
        cin >> iv;

        Usuario* u = &usuarios[iu];
        Vuelo* v = &vuelos[iv];

        float precio = v->getPrecio();

        if (u->getKmAcumulados() > 50000) {
            precio *= 0.6; // 40% descuento
        }

        u->acumulaKm(v->getDistanciaKm());

        reservaciones[numReservaciones++] = Reservacion(u, v, precio);

        cout << "Reservacion creada. Precio final: $" << precio << "\n";
    }

    // ------------------------------
    void mostrarReservaciones() {
        for (int i = 0; i < numReservaciones; i++) {
            cout << i << ") Usuario: " << reservaciones[i].getUsuario()->getNombre()
                 << ", Vuelo: " << reservaciones[i].getVuelo()->getNumeroVuelo()
                 << ", Precio: $" << reservaciones[i].getPrecioFinal()
                 << ", Activa: " << (reservaciones[i].getActiva() ? "Si" : "No")
                 << "\n";
        }
    }

    // ------------------------------
    void cancelarReservacion() {
        mostrarReservaciones();
        cout << "Numero de reservacion a cancelar: ";
        int r;
        cin >> r;

        reservaciones[r].cancelar();
        cout << "Reservacion cancelada.\n";
    }
};

#endif
