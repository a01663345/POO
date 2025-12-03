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
            cout << "3) Dar de alta usuario\n";
            cout << "4) Mostrar usuarios\n";
            cout << "5) Realizar reservacion\n";
            cout << "6) Imprime reservaciones\n";
            cout << "7) Cancelar reservacion\n";
            cout << "8) Salir\n";
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
                    agregarUsuario(); 
                break;
                case 4: 
                    mostrarUsuarios(); 
                break;
                case 5: 
                    realizarReservacion(); 
                break;
                case 6: 
                    mostrarReservaciones(); 
                break;
                case 7: 
                    cancelarReservacion(); 
                break;
                case 8: 
                    cout << "Saliendo...\n" << endl;
                break;
                default: 
                    cout << "Opcion invalida.\n" << endl;
                break;
            }

        } while (opcion != 8);
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
    // BUSCAR VUELO POR FECHA
    // ------------------------------
    void buscarVueloPorFecha() {
        if (numVuelos == 0) {
            cout << "No hay vuelos registrados para buscar.\n";
            return;
        }

        string f;
        cout << "Ingrese la fecha a buscar (mismo formato usado al registro): ";
        cin >> f;

        bool encontrado = false;
        cout << "\n--- Resultados de busqueda para fecha: " << f << " ---\n";
        
        for (int i = 0; i < numVuelos; i++) {
            if (vuelos[i].getFecha() == f) {
                cout << "Vuelo " << vuelos[i].getNumeroVuelo()
                     << " (" << vuelos[i].getAerolinea() << ")"
                     << " - Hora/Duracion: " << vuelos[i].getDuracionMin() << " min"
                     << " - Precio: $" << vuelos[i].getPrecio() << "\n";
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron vuelos en esa fecha.\n";
        }
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
