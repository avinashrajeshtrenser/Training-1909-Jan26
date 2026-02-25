using namespace std;
#include "FileManager.h"

void FileManager::saveDeliveries(const vector<Delivery>& deliveries, const string& fileName)
{
    ofstream file(fileName);
    for (vector<Delivery>::const_iterator deliveryIterator = deliveries.begin(); deliveryIterator != deliveries.end(); ++deliveryIterator)
    {
        int storeId = -1;
        int vehicleId = -1;
        if (deliveryIterator->getStore())
        {
            storeId = deliveryIterator->getStore()->getStoreId();
        }
        if (deliveryIterator->getVehicle())
        {
            vehicleId = deliveryIterator->getVehicle()->getVehicleId();
        }
        file << deliveryIterator->getDeliveryId() << "|"
            << to_string(static_cast<int>(deliveryIterator->getDeliveryStatus())) << "|"
            << deliveryIterator->getDeliveryAddress() << "|"
            << storeId << "|"
            << vehicleId << "|";
        const vector<DeliveryItem>& items = deliveryIterator->getItems();
        for (vector<DeliveryItem>::const_iterator itemIterator = items.begin(); itemIterator != items.end(); ++itemIterator)
        {
            if (itemIterator->getProduct())
            {
                file << itemIterator->getProduct()->getProductId() << ":" << itemIterator->getQuantity();
                if (itemIterator + 1 != items.end())
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
    try
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
            stringstream deliveryStream(line);
            string token;
            int deliveryId;
            DeliveryStatus status;
            string address;
            int storeId;
            int vehicleId;
            string itemsPart;
            getline(deliveryStream, token, '|');
            deliveryId = stoi(token);
            getline(deliveryStream, token, '|');
            if (stoi(token) < static_cast<int>(DeliveryStatus::PENDING_DISPATCH) && stoi(token) > static_cast<int>(DeliveryStatus::DELIVERED))
            {
                throw runtime_error("Invalid Delivery Status");
            }
            status = static_cast<DeliveryStatus>(stoi(token));
            getline(deliveryStream, address, '|');
            getline(deliveryStream, token, '|');
            storeId = stoi(token);
            getline(deliveryStream, token, '|');
            vehicleId = stoi(token);
            getline(deliveryStream, itemsPart);
            shared_ptr<Store> store = nullptr;
            shared_ptr<Vehicle> vehicle = nullptr;
            for (auto storeIterator = stores.begin(); storeIterator != stores.end(); ++storeIterator)
            {
                if ((*storeIterator)->getStoreId() == storeId)
                {
                    store = *storeIterator;
                    break;
                }
            }
            for (auto vehicleIterator = vehicles.begin(); vehicleIterator != vehicles.end(); ++vehicleIterator)
            {
                if ((*vehicleIterator)->getVehicleId() == vehicleId)
                {
                    vehicle = *vehicleIterator;
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
                        for (vector<shared_ptr<Product>>::const_iterator productIterator = products.begin(); productIterator != products.end(); ++productIterator)
                        {
                            if ((*productIterator)->getProductId() == productId)
                            {
                                matchedProduct = *productIterator;
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
    catch (const exception& e)
    {
        cout << e.what() << "Error parsing line./n";
    }
}
void FileManager::saveDispatchQueue(const vector<DeliveryItem>& dispatchQueue, const string& fileName)
{
    ofstream file(fileName);
    for (vector<DeliveryItem>::const_iterator iterator = dispatchQueue.begin(); iterator != dispatchQueue.end(); ++iterator)
    {
        if (iterator->getProduct() && iterator->getStore())
        {
            file << iterator->getProduct()->getProductId() << "|" << iterator->getStore()->getStoreId() << "|" << iterator->getQuantity() << "\n";
        }
    }
}

void FileManager::loadDispatchQueue(vector<DeliveryItem>& dispatchQueue, const vector<shared_ptr<Product>>& products, const vector<shared_ptr<Store>>& stores, const string& fileName)
{
    ifstream file(fileName);
    if (!file) 
    {
        return;
    }
    dispatchQueue.clear();
    string line;
    while (getline(file, line))
    {
        stringstream queueStream(line);
        string token;
        int productId;
        int storeId;
        int quantity;
        getline(queueStream, token, '|');
        productId = stoi(token);
        getline(queueStream, token, '|');
        storeId = stoi(token);
        getline(queueStream, token, '|');
        quantity = stoi(token);
        shared_ptr<Product> matchedProduct = nullptr;
        shared_ptr<Store> matchedStore = nullptr;
        for (auto productIterator = products.begin(); productIterator != products.end(); ++productIterator)
        {
            if ((*productIterator)->getProductId() == productId)
            {
                matchedProduct = *productIterator;
                break;
            }
        }
        for (auto storeIterator = stores.begin(); storeIterator != stores.end(); ++storeIterator)
        {
            if ((*storeIterator)->getStoreId() == storeId)
            {
                matchedStore = *storeIterator;
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