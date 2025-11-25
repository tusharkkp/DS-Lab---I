#include <iostream>
using namespace std;

struct Order {
    int orderID;
    Order* next;
};

class PizzaParlor {
private:
    Order* front;
    Order* rear;
    int currentSize;
    int maxOrders;

public:
    PizzaParlor(int maxOrders) {
        this->maxOrders = maxOrders;
        front = rear = NULL;
        currentSize = 0;
    }

    void placeOrder(int orderID) {
        if (currentSize == maxOrders) {
            cout << "Sorry! We can't accept more orders. Maximum order limit reached.\n";
            return;
        }

        Order* newOrder = new Order();
        newOrder->orderID = orderID;
        newOrder->next = NULL;

        if (front == NULL) {
            front = rear = newOrder;
            newOrder->next = front;
        } else {
            rear->next = newOrder;
            rear = newOrder;
            rear->next = front;
        }

        currentSize++;
        cout << "Order " << orderID << " placed successfully.\n";
    }

    void serveOrder() {
        if (currentSize == 0) {
            cout << "No orders to serve.\n";
            return;
        }

        Order* temp = front;
        cout << "Serving order " << front->orderID << ".\n";
        front = front->next;
        rear->next = front;

        delete temp;
        currentSize--;
    }

    void viewOrders() {
        if (currentSize == 0) {
            cout << "No orders in the system.\n";
            return;
        }

        Order* temp = front;
        cout << "Current orders: ";
        do {
            cout << temp->orderID << " ";
            temp = temp->next;
        } while (temp != front);
        cout << endl;
    }

    ~PizzaParlor() {
        while (currentSize > 0) {
            serveOrder();
        }
    }
};

int main() {
    int maxOrders;
    cout << "Enter the maximum number of orders that can be accepted: ";
    cin >> maxOrders;

    PizzaParlor parlor(maxOrders);

    int choice, orderID;

    do {
        cout << "\nPizza Parlor Menu:\n";
        cout << "1. Place Order\n";
        cout << "2. Serve Order\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter order ID: ";
                cin >> orderID;
                parlor.placeOrder(orderID);
                break;
            case 2:
                parlor.serveOrder();
                break;
            case 3:
                parlor.viewOrders();
                break;
            case 4:
                cout << "Exiting the system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

