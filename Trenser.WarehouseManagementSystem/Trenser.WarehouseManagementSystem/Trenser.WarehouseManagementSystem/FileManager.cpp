using namespace std;
#include "FileManager.h"

void FileManager::saveDeliveries(const vector<Delivery>& deliveries, const string& fileName)
{
    ofstream file(fileName);
    for (vector<Delivery>::const_iterator it = deliveries.begin(); it != deliveries.end(); ++it)
    {
        int storeId = -1;
        int vehicleId = -1;
        if (it->getStore())
        {
            storeId = it->getStore()->getStoreId();
        }
        if (it->getVehicle())
        {
            vehicleId = it->getVehicle()->getVehicleId();
        }
        file << it->getDeliveryId() << "|"
            << it->getDeliveryStatus() << "|"
            << it->getDeliveryAddress() << "|"
            << storeId << "|"
            << vehicleId << "|";
        const vector<DeliveryItem>& items = it->getItems();
        for (vector<DeliveryItem>::const_iterator itemIt = items.begin(); itemIt != items.end(); ++itemIt)
        {
            if (itemIt->getProduct())
            {
                file << itemIt->getProduct()->getProductId() << ":" << itemIt->getQuantity();
                if (itemIt + 1 != items.end())
                {
                    file << ",";
                }
            }
        }
        file << "\n";
    }
}

void FileManager::loadDeliveries(vector<Delivery>& deliveries, const vector<shared_ptr<Store>>& stores, const vector<shared_ptr<Vehicle>>& vehicles, const vector<shared_ptr<Product>>& products, const string& fileName)
{
    ifstream file(fileName);
    if (!file)
    {
        return;
    }
    deliveries.clear();
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        int deliveryId;
        string status;
        string address;
        int storeId;
        int vehicleId;
        string itemsPart;
        getline(ss, token, '|');
        deliveryId = stoi(token);
        getline(ss, status, '|');
        getline(ss, address, '|');
        getline(ss, token, '|');
        storeId = stoi(token);
        getline(ss, token, '|');
        vehicleId = stoi(token);
        getline(ss, itemsPart);
        shared_ptr<Store> store = nullptr;
        shared_ptr<Vehicle> vehicle = nullptr;
        for (auto it = stores.begin(); it != stores.end(); ++it)
        {
            if ((*it)->getStoreId() == storeId)
            {
                store = *it;
                break;
            }
        }
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it)
        {
            if ((*it)->getVehicleId() == vehicleId)
            {
                vehicle = *it;
                break;
            }
        }
        Delivery delivery(deliveryId, address, store, vehicle);
        delivery.updateDeliveryStatus(status);
        if (!itemsPart.empty())
        {
            stringstream itemsStream(itemsPart);
            string itemToken;
            while (getline(itemsStream, itemToken, ','))
            {
                size_t separatorPosition = itemToken.find(':');
                if (separatorPosition != string::npos)
                {
                    int productId = stoi(itemToken.substr(0, separatorPosition));
                    int quantity = stoi(itemToken.substr(separatorPosition + 1));
                    shared_ptr<Product> matchedProduct = nullptr;
                    for (vector<shared_ptr<Product>>::const_iterator productIt = products.begin(); productIt != products.end(); ++productIt)
                    {
                        if ((*productIt)->getProductId() == productId)
                        {
                            matchedProduct = *productIt;
                            break;
                        }
                    }
                    if (matchedProduct && store)
                    {
                        DeliveryItem deliveryItem(quantity, matchedProduct, store);
                        delivery.getItems().push_back(deliveryItem);
                    }
                }
            }
        }
        deliveries.push_back(delivery);
    }
}
void FileManager::saveDispatchQueue(const vector<DeliveryItem>& dispatchQueue, const string& fileName)
{
    ofstream file(fileName);
    for (vector<DeliveryItem>::const_iterator it = dispatchQueue.begin(); it != dispatchQueue.end(); ++it)
    {
        if (it->getProduct() && it->getStore())
        {
            file << it->getProduct()->getProductId() << "|" << it->getStore()->getStoreId() << "|" << it->getQuantity() << "\n";
        }
    }
}

void FileManager::loadDispatchQueue(vector<DeliveryItem>& dispatchQueue, const vector<shared_ptr<Product>>& products, const vector<shared_ptr<Store>>& stores, const string& fileName)
{
    ifstream file(fileName);
    if (!file) return;
    dispatchQueue.clear();
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        int productId;
        int storeId;
        int quantity;
        getline(ss, token, '|');
        productId = stoi(token);
        getline(ss, token, '|');
        storeId = stoi(token);
        getline(ss, token, '|');
        quantity = stoi(token);
        shared_ptr<Product> matchedProduct = nullptr;
        shared_ptr<Store> matchedStore = nullptr;
        for (auto pit = products.begin(); pit != products.end(); ++pit)
        {
            if ((*pit)->getProductId() == productId)
            {
                matchedProduct = *pit;
                break;
            }
        }
        for (auto sit = stores.begin(); sit != stores.end(); ++sit)
        {
            if ((*sit)->getStoreId() == storeId)
            {
                matchedStore = *sit;
                break;
            }
        }
        if (matchedProduct && matchedStore)
        {
            dispatchQueue.push_back(DeliveryItem(quantity, matchedProduct, matchedStore));
        }
    }
}

void FileManager::saveRejectedItems(const vector<DeliveryItem>& rejectedItems, const string& fileName)
{
    saveDispatchQueue(rejectedItems, fileName);
}

void FileManager::loadRejectedItems(vector<DeliveryItem>& rejectedItems, const vector<shared_ptr<Product>>& products, const vector<shared_ptr<Store>>& stores, const string& fileName)
{
    loadDispatchQueue(rejectedItems, products, stores, fileName);
}