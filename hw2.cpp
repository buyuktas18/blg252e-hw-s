#include <iostream>
#include <string>

using namespace std;


class Person{
public:
    string name;
    string surname;
};


class Owner : public Person{
public:
    float ownership;
    Owner(string, string);
    Owner();
};

Owner::Owner(){
    this->name = "Deniz";
    this->surname = "Buyuktas";
}

Owner::Owner(string name, string surname){
    this->name = name;
    this->surname = surname;
}

class Courier : public Person{
public:
    string vehicle;
    Courier(string, string, string);
    bool operator==(Courier&);
};

Courier::Courier(string name, string surname, string vehicle){
    this->name = name;
    this->surname = surname;
    this->vehicle = vehicle;
}



class List : public Courier{
    public:
    List *next;
    List(string, string, string);
}; 
List::List(string name, string surname, string vehicle): Courier(name, surname, vehicle){
    next = NULL;

}

class Business{
    string name;
    string address;
    Owner* list;
    List *head = NULL;
    int owner_count;
    public:
    void list_owners();
    Business(string, string, Owner*, int);
    void hire_courier(Courier &to_hire);
    void list_couriers();
    void operator()();
    void operator==(Courier&);
    void fire_courier(Courier&);
    Courier& operator[](int);
    int calculate_shipment_capacity();
    ~Business();
};

Business::~Business(){
    delete [] list;
    List* traverse;
    while(head){
        traverse = head;
        head = head->next;
        delete traverse;
    }
    delete head;
}

int Business::calculate_shipment_capacity(){
    int shipment = 0;
    List* traverse = head;
    while(traverse){
        if(traverse->vehicle == "bicycle"){
            shipment += 10;
        }
        else if(traverse->vehicle == "motorcycle"){
            shipment += 35;
        }
        else{
            shipment += 200;
        }
        traverse = traverse->next;
    }
    return shipment;
}

Courier& Business::operator[](int a){
    int counter = 0;
    
    List* traverse = head;
    while(true){
        if(a == counter){
            break;
        }
        else{
            traverse = traverse->next;
            counter++;
        }
    }
    return *traverse;

}

void Business::fire_courier(Courier& to_fire){
    List* traverse = head;
    List* back = NULL;
    while(true){
        while(!(*traverse == to_fire) && traverse->next){
            back = traverse;
            traverse = traverse->next;
        }
        if(!traverse->next && !(*traverse == to_fire)){
            cout<<"Courier couldn't found"<<endl;
            break;
        }
        else{
            if(!back){ 
            head = head->next;
            
            
            }
            else{
                back->next = traverse->next;
            }
            delete traverse;
            }
            break;
        }
        

    }
     
bool Courier::operator==(Courier& to_fire){
    return(this->name == to_fire.name && this->surname == to_fire.surname && this->vehicle == to_fire.vehicle);


}

void Business::list_couriers(){
    List* traverse = head;
    while(traverse){
        cout<<traverse->name<<" "<<traverse->surname<<" "<<traverse->vehicle<<endl;
        traverse = traverse->next;
        
    }
}

void Business::operator()(){
    cout<<this->name<<" "<<this->address<<endl;
    this->list_owners();
    this->list_couriers();
}

void Business::hire_courier(Courier &to_hire){
    List *temp = new List("", "", ""); 
    temp->name = to_hire.name;
    temp->surname = to_hire.surname;
    temp->vehicle = to_hire.vehicle;
    if(!head){
        
        head = temp;
        head->next = NULL;
    }
    else{
        List* traverse = head;
        while(traverse->next){
            traverse = traverse->next;
        }
        traverse->next = temp;
        traverse->next->next = NULL;
    }
}

Business::Business(string name, string address, Owner* list, int a){
    this->name = name;
    this->address = address;
    this->list = list;
    owner_count = a;
}

void Business::list_owners(){
    for(int i = 0; i < owner_count; i++){
        cout<<list[i].name<<" "<<list[i].surname<<" "<<100.0/owner_count<<endl;
    }
}

int main(){
    // Create owners of the business
    //Constructor parameters: name, surname
    Owner o1 = Owner("Owner_name1", "surname1");
    Owner o2 = Owner("Owner_name2", "surname2");
    Owner* owner_arr = new Owner[2];
    owner_arr[0] = o1;
    owner_arr[1] = o1;    

    //Crete the business itself
    //Constructor parameters: name, address, owner_array, number_of_owners
    Business atlas = Business("Atlas", "Maslak Istanbul/Turkey", owner_arr, 2);
    
    // Print owner info to screen: name, surname, ownership
    atlas.list_owners();

    // Add new employees
    // Constructor parameters: name, surname, vehicle_type
    Courier c1 = Courier("Courier", "surname1", "car");
    Courier c2 = Courier("Courier", "surname2", "motorcycle");
    Courier c3 = Courier("Courier", "surname3", "motorcycle");    

    atlas.hire_courier(c1);
    atlas.hire_courier(c2);
    atlas.hire_courier(c3);


    // Print business info to screen
    // Name, address, owners, couriers

    atlas();

    // Get courier with index 1 and remove it from the list/array
    Courier cour = atlas[1];
    atlas.fire_courier(cour);
    // Print remaining couriers
    atlas.list_couriers();
    Courier c4 = Courier("Deniz", "Buyuktas", "car");
    atlas.hire_courier(c4);
    atlas.list_couriers();
    atlas.fire_courier(c1);
    atlas.fire_courier(atlas[0]);
    // Print remaining couriers
    atlas.list_couriers();
    // Print current maximum shipment capacity
    std::cout << atlas.calculate_shipment_capacity() << std::endl;
    return 0;
}