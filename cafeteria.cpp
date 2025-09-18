#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QPalette>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <iostream>
#include <QVBoxLayout>
#include <QFile>
using namespace std;

struct MenuItem {
    QString Name;
    int Code;
    float Price;
    int Stock;
};
struct OrderItem{
int itemCode;
int itemQuantity;
};
class MyWindow : public QWidget {
public:
    MyWindow() {
        setFixedSize(1170, 584); //fixed window size
        layout = new QVBoxLayout(this);

        initMenu();
        showInitialLayout();
        
    }

private:
    const int menuSize = 17;
    MenuItem menu[17];
    QVBoxLayout* layout;
    int orderSize = 0;
    OrderItem* order = nullptr;
    string discountvoucher[4] = {"FIRSTORDER10", "ONLINE10", "FAMILYFUN", "ONLINE25"};
    int choice;
    void readStockFile() {
        QFile file("./StockInfo.txt");  // Using Qt's QFile for file handling
        int j;

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
          
            for (int i = 0; i < menuSize; i++) {
                j = 0;
                bool flag = false;
                QString line = in.readLine();     // Reading names (full lines)
                
                for (QChar ch : line) {
                    if (ch.isDigit()) {
                        flag = true;
                        break;
                    }
                    menu[i].Name += ch;  
                }

                if (flag) {
                    continue;  // Skiping to the next iteration if we encounter a digit
                }
            }
            // Move file pointer to the beginning 
            file.seek(0);

            // Reading integers and saving into respective fields
            for (int i = 0; i < menuSize; i++) {
                QString word1, word2;
                in >> word1 >> word2 >> menu[i].Code >> menu[i].Price >> menu[i].Stock;
            }

            file.close();  
            cout << "Stock loaded from file successfully.\n";
        } else {
            cout << "Error loading stock from file. Using default stock values.\n";
        }
    }
    void saveStockFile() {
        QFile file("./StockInfo.txt");  // Opening file & writing menu info
        
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int i = 0; i < menuSize; i++) {
                out << menu[i].Name << " "
                    << menu[i].Code << " "
                    << menu[i].Price << " "
                    << menu[i].Stock << "\n";
            }

            file.close();  // file closure after writing
            cout << "Stock saved to file successfully.\n";
        } else {
            cout << "Error saving stock to file.\n";
        }
    }
    void saveSalesFile(QString sale){
        QFile file("./SalesFile.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);

            out<<sale<<"\n";
            file.close();
            cout<<"Sale saved to file successfully"<<endl;
        }
        else{
            cout<<"Error savinf stock to file"<<endl;
        }
    }
    void initMenu() {
        QFile file("./StockInfo.txt");  // Replacing with our file path
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Could not open file.");
            return;
        }
        if (file.size() == 0) {  // Checking if the file size is 0
            menu[0] = {"Smash Burger", 1001, 1299.0, 20};
            menu[1] = {"Moroccan Chicken", 1002, 1590.0, 20};
            menu[2] = {"Margherita Pizza", 1003, 1050.0, 20};
            menu[3] = {"Chicken Lasagne", 1004, 999.0, 20};
            menu[4] = {"Fettuccini Pasta", 1005, 1100.0, 20};
            menu[5] = {"Blueberry Pancakes", 1006, 495.0, 20};
            menu[6] = {"Chocolate Waffles", 1007, 655.0, 20};
            menu[7] = {"French Toast", 1008, 450.4, 20};
            menu[8] = {"Hash browns", 1009, 400.0, 20};
            menu[9] = {"Smoothie bowl", 1010, 699.0, 20};
            menu[10] = {"Molten Cake", 1011, 599.0, 20};
            menu[11] = {"Banana pie", 1012, 545.6, 20};
            menu[12] = {"Cheese cake", 1013, 744.6, 20};
            menu[13] = {"Mint brownie", 1014, 534.4, 20};
            menu[14] = {"Coconut water", 1015, 445.6, 20};
            menu[15] = {"Iced tea", 1016, 234.4, 20};
            menu[16] = {"Mint Margarita", 1018, 240.4, 20};
            saveStockFile();
        }
        else{
            readStockFile();
        }
        file.close();
    }
    void clearLayout() {
            // Clear all widgets in the layout without deleting them
            QLayoutItem* item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget(); // Delete widget if exists
                delete item; // Delete layout item
            }
    }
    void showInitialLayout() {
        clearLayout();
        
        // welcome label
        QLabel* welcomeLabel = new QLabel("Welcome to S&H Kitchen!", this);
        welcomeLabel->setStyleSheet("font-size: 40px; font-family: 'American Typewriter'; font-weight: bold; color: black;");
        welcomeLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(welcomeLabel);

        // Creating buttons
        QPushButton* button1 = new QPushButton("View Menu", this);
        button1->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(button1);

        QPushButton* button2 = new QPushButton("Place Order", this);
        button2->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(button2);

        QPushButton* button3 = new QPushButton("Modify Order", this);
        button3->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(button3);

        QPushButton* button4 = new QPushButton("View Cart", this);
        button4->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(button4);

        QPushButton* button5 = new QPushButton("Confirm Order", this);
        button5->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(button5);

        QPushButton* button6 = new QPushButton("Exit", this);
        button6->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(button6);

        // Connecting buttons to the slots
        connect(button1, &QPushButton::clicked, this, &MyWindow::viewMenu);
        connect(button2, &QPushButton::clicked, this, &MyWindow::placeOrder);
        connect(button3, &QPushButton::clicked, this, &MyWindow::modifyOrder);
        connect(button4, &QPushButton::clicked, this, &MyWindow::viewCart);
        connect(button5, &QPushButton::clicked, this, &MyWindow::confirmOrder);
        connect(button6, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
    }
    void viewMenu() {
        clearLayout();

        QSpacerItem* topSpacer = new QSpacerItem(0, 85, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(topSpacer);

        QLabel* menuTitle = new QLabel("Menu:", this);
        menuTitle->setStyleSheet("font-size: 15px; font-family: 'American Typewriter'; color: black; font-weight: bold;");
        layout->addWidget(menuTitle);

        for (int i = 0; i < menuSize; ++i) {
            QString menuItemText = QString("%1 - Code: %2 - Price: Rs.%3")
                                    .arg(menu[i].Name)
                                    .arg(menu[i].Code)
                                    .arg(menu[i].Price);

            QLabel* menuItemLabel = new QLabel(menuItemText, this);
            menuItemLabel->setStyleSheet("font-size: 15px; font-family: 'Courier New'; color: black;");
            layout->addWidget(menuItemLabel);
        }

        QSpacerItem* bottomSpacer = new QSpacerItem(100, -90, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(bottomSpacer);

        QPushButton* backButton = new QPushButton("Back", this);
        backButton->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter';");
        layout->addWidget(backButton);
        backButton->setFixedSize(1100, 18);

        connect(backButton, &QPushButton::clicked, this, &MyWindow::showInitialLayout);

    }
    void placeOrder() {
        clearLayout(); 
    

        QSpacerItem* placeSpacer = new QSpacerItem(0, -15, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(placeSpacer);//formatting
        QLabel* itemCodeLabel = new QLabel("Enter item code:", this);
        itemCodeLabel->setStyleSheet("font-size: 18px; font-family: 'American Typewriter'; color: black;font-weight: bold");
        QLineEdit* itemCodeInput = new QLineEdit(this);
        // item code input
        itemCodeInput->setPlaceholderText("Enter Item Code...");
        itemCodeInput->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black;background-color: white;");
        layout->addWidget(itemCodeLabel);
        layout->addWidget(itemCodeInput);
        QSpacerItem* placeSpacer1 = new QSpacerItem(0, -15, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(placeSpacer1);//formatting
        // Quantity input
        QLabel* quantityLabel = new QLabel("Enter quantity:", this);
        quantityLabel->setStyleSheet("font-size: 18px; font-family: 'American Typewriter'; color: black;font-weight: bold");
        QLineEdit* quantityInput = new QLineEdit(this);
        quantityInput->setPlaceholderText("Enter Quantity...");
        quantityInput->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black;background-color: white;");
        layout->addWidget(quantityLabel);
        layout->addWidget(quantityInput);
        QSpacerItem* placeSpacer2 = new QSpacerItem(0, -15, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(placeSpacer2);//formatting
    
        // Confirm order button
        QPushButton* confirmButton = new QPushButton("Place Order", this);
        confirmButton->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(confirmButton);
        connect(confirmButton, &QPushButton::clicked, [this, itemCodeInput, quantityInput]() {
            bool ok;
            int itemCode = itemCodeInput->text().toInt(&ok); // item code input
            if (!ok || itemCode <= 0) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid item code.");
                return;
            }

            int quantity = quantityInput->text().toInt(&ok); // quantity input
            if (!ok || quantity <= 0) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid quantity.");
                return;
            }

            bool itemFound = false;

            for (int i = 0; i < menuSize; ++i) {
                if (menu[i].Code == itemCode) {
                    itemFound = true;
                    if (quantity > menu[i].Stock) {
                        // if quantity added exceeds stock
                        QMessageBox::warning(this, "Stock Exceeded", QString("Only %1 items in stock.").arg(menu[i].Stock));
                    } else {
                        for (int j = 0; j < orderSize; j++){
                            if (order[i].itemCode==itemCode){
                                QMessageBox::information(this, "Message", QString("Item already in cart. Modify order if you wish to change quantity."));
                                return;
                            }
                        }
                        // Updating stock and processing order
                        menu[i].Stock = menu[i].Stock - quantity;
                        QMessageBox::information(this, "Order Placed", QString("You have ordered %1 of %2.").arg(quantity).arg(menu[i].Name));
                        saveStockFile();
                        OrderItem* newOrder = new OrderItem[orderSize + 1];  
                        for (int j = 0; j < orderSize; ++j) {
                            newOrder[j] = order[j]; 
                        }
                        newOrder[orderSize].itemCode = itemCode;
                        newOrder[orderSize].itemQuantity = quantity;
                        delete[] order;  
                        order = newOrder;  
                        orderSize++;  
                        
                        break; 
                    }
                    break;
                }
            }

            if (!itemFound) {
                // item code is not valid
                QMessageBox::warning(this, "Invalid Item Code", "The entered item code is invalid.");
            }
        });
        // Back button (leads to main screen)
        QPushButton* backButton = new QPushButton("Back", this);
        backButton->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        connect(backButton, &QPushButton::clicked, this, &MyWindow::showInitialLayout);
        layout->addWidget(backButton);
    }

    void changeQuantity(){
        clearLayout();
        QSpacerItem* changeqSpacer = new QSpacerItem(0, -15, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(changeqSpacer);// formatting
        QLabel* itemCodeLabel = new QLabel("Enter item code:", this);
        itemCodeLabel->setStyleSheet("font-size: 18px; font-family: 'American Typewriter'; color: black;font-weight: bold");
        QLineEdit* itemCodeInput = new QLineEdit(this);
        itemCodeInput->setPlaceholderText("Enter Item Code...");
        itemCodeInput->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black;background-color: white;");
        layout->addWidget(itemCodeLabel);
        layout->addWidget(itemCodeInput);
        QSpacerItem* changeqSpacer2= new QSpacerItem(0, -15, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(changeqSpacer2);//formatting

        QLabel* quantityLabel = new QLabel("Enter quantity:", this);
        quantityLabel->setStyleSheet("font-size: 18px; font-family: 'American Typewriter'; color: black;font-weight: bold");
        QLineEdit* quantityInput = new QLineEdit(this);
        quantityInput->setPlaceholderText("Enter Quantity...");
        quantityInput->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black;background-color: white;");
        layout->addWidget(quantityLabel);
        layout->addWidget(quantityInput);

        QSpacerItem* changeqSpacer3 = new QSpacerItem(0, -15, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(changeqSpacer3);//formatting
        QPushButton* confirmButton = new QPushButton("Confirm", this);
        confirmButton->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(confirmButton);

        connect(confirmButton, &QPushButton::clicked, [this, itemCodeInput, quantityInput]() {
            bool ok;
            int itemCode = itemCodeInput->text().toInt(&ok); //item code input
            if (!ok || itemCode <= 0) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid item code.");
                return;
            }

            int quantity = quantityInput->text().toInt(&ok); //quantity input
            if (!ok || quantity <= 0) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid quantity.");
                return;
            }
            bool itemFound = false;

            // Loop through the menu to find the item with the entered code
            for (int i = 0; i < orderSize; i++) {
                if (order[i].itemCode == itemCode) {
                    itemFound = true;
                    for (int j = 0; j < menuSize; j++){
                        int change = quantity - order[i].itemQuantity;
                        //order[i].itemQuantity = quantity;
                        if (change > 0 && change > menu[j].Stock){
                            QMessageBox::warning(this, "Stock Alert", QString("Not enough stock available. Only %1 left.").arg(menu[j].Stock));
                            return;
                        }
                        menu[j].Stock = menu[j].Stock - quantity;
                        saveStockFile();
                        order[i].itemQuantity = quantity;
                        QMessageBox::information(this, "Success", "Quantity updated successfully!");
                        return;
                    }
                }
            }

            if (!itemFound) {
               
                QMessageBox::warning(this, "Invalid Item Code", "The entered item code is invalid.");
            }
        });
        QPushButton* backButton = new QPushButton("Back", this);
        backButton->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter';border-radius: 10px; padding: 5px;");
        connect(backButton, &QPushButton::clicked, this, &MyWindow::showInitialLayout);
        layout->addWidget(backButton);
    }
    void deleteItem(){
        clearLayout();
        QLabel* itemCodeLabel = new QLabel("Enter item code:", this);
        itemCodeLabel->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black;");
        QLineEdit* itemCodeInput = new QLineEdit(this);
        itemCodeInput->setPlaceholderText("Item Code...");
        itemCodeInput->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black;background-color: white;");
        layout->addWidget(itemCodeLabel);
        layout->addWidget(itemCodeInput);
        QSpacerItem* deleteSpacer = new QSpacerItem(6, 279); //spacers used for formatting throught the code
        layout->addItem(deleteSpacer);

        QPushButton* confirmButton = new QPushButton("Confirm", this);
        confirmButton->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(confirmButton);
        connect(confirmButton, &QPushButton::clicked, [this, itemCodeInput]() {
            bool ok;
            int itemCode = itemCodeInput->text().toInt(&ok); // Getting item code input
            if (!ok || itemCode <= 0) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid item code.");
                return;
            }
            // Searching for the item code in the order array
            int index = -1;
            for (int i = 0; i < orderSize; ++i) {
                if (order[i].itemCode == itemCode) {
                    index = i;
                    break;
                }
            }

            if (index != -1) {
                // Creating a new order array with one less item
                OrderItem* newOrder = new OrderItem[orderSize - 1];
                int j = 0;
                for (int i = 0; i < orderSize; ++i) {
                    if (i != index) {
                        newOrder[j] = order[i];
                        ++j;
                    }
                    else{
                        for (int k = 0; k < menuSize; k++){
                            if (menu[k].Code == order[i].itemCode){
                                menu[k].Stock = menu[k].Stock + order[i].itemQuantity;
                                saveStockFile();
                                break;
                            }
                        }
                    }
                }
                delete[] order;   // Free the old order memory
                order = newOrder; // Update the order pointer
                orderSize--;      // Decrease the order size

                QMessageBox::information(this, "Item Deleted", QString("Item with code %1 has been deleted from the cart.").arg(itemCode));
            } else {
                // If item code not found
                QMessageBox::warning(this, "Item Not Found", QString("Item with code %1 does not exist in the cart.").arg(itemCode));
            }
        
        });
        QPushButton* backButton = new QPushButton("Back", this);
        backButton->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        connect(backButton, &QPushButton::clicked, this, &MyWindow::showInitialLayout);
        layout->addWidget(backButton);
    }
    void modifyOrder() {
        clearLayout();
        if (orderSize == 0){
             
            QLabel* emptyLabel = new QLabel("Your cart is empty!",this);
            emptyLabel->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; font-weight: bold;");
            layout->addWidget(emptyLabel);
            QSpacerItem* bottomSpacer = new QSpacerItem(6, 279);
            layout->addItem(bottomSpacer);
           
        }
        else{
                //cart isn't empty so the user can either modify or delete items
         QSpacerItem* voucherSpacer = new QSpacerItem(6, 270);
            layout->addItem(voucherSpacer);
            QPushButton* quantityChange = new QPushButton("Change Quantity", this);
            quantityChange->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter'; border-radius: 10px; padding: 5px;");
            layout->addWidget(quantityChange);
            QPushButton* itemDelete = new QPushButton("Delete Item", this);
            itemDelete->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter'; border-radius: 10px; padding: 5px;");
            layout->addWidget(itemDelete);


            connect(itemDelete, &QPushButton::clicked, this, &MyWindow::deleteItem);
            connect(quantityChange, &QPushButton::clicked, this, &MyWindow::changeQuantity);
            QSpacerItem* bottomSpacer = new QSpacerItem(0, 10);
            layout->addItem(bottomSpacer);


        }
        //back to main screen if backbutton clicked
        QPushButton* backButton = new QPushButton("Back", this);
        connect(backButton, &QPushButton::clicked, this, &MyWindow::showInitialLayout);
        backButton->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(backButton);
        
    }

    void viewCart() {

        clearLayout();
            
        if (orderSize == 0) {
        
            QLabel* emptyLabel = new QLabel("Your cart is empty!", this);
            emptyLabel->setStyleSheet("font-size: 16px; font-family: 'American Typewriter'; color: black; font-weight: bold;");
            layout->addWidget(emptyLabel);
            QSpacerItem* cartSpacer = new QSpacerItem(6, 279);
            layout->addItem(cartSpacer);
        } else {
            QSpacerItem* goodSpacer = new QSpacerItem(0, 500);
            layout->addItem(goodSpacer);
            // Loop to check items and display items one by one
            for (int i = 0; i < orderSize; i++) {
                for (int j = 0; j < menuSize; j++) {
                  
                    if (order[i].itemCode == menu[j].Code) {
                        
                        QString itemText = QString("%1 (Code: %2) -- Rs.%3 x %4")
                            .arg(menu[j].Name)              
                            .arg(menu[j].Code)              
                            .arg(menu[j].Price, 0, 'f', 2)    
                            .arg(order[i].itemQuantity);   

                        QLabel* itemLabel = new QLabel(itemText, this);
                        itemLabel->setStyleSheet("font-size: 12px; font-family: 'American Typewriter'; color: black;");
                        layout->addWidget(itemLabel);
                    }
                }
            }
        }
   
         // back button to go back to the main screen
        QPushButton* backButton = new QPushButton("Back", this);
         backButton->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter';border-radius: 10px; padding: 5px;");
        layout->addWidget(backButton);
        connect(backButton, &QPushButton::clicked, this, &MyWindow::showInitialLayout);
    }
    void confirmOrder() {
        clearLayout(); 
            QSpacerItem* confirmorderSpacer = new QSpacerItem(6, 100);
            layout->addItem(confirmorderSpacer);
        float bill = 0;
        const double TAX = 0.05;
        saveSalesFile("Sale");
     
        for (int i = 0; i < orderSize; i++) {
            for (int j = 0; j < menuSize; j++) {
                if (order[i].itemCode == menu[j].Code) {
              
                float itemSubtotal = order[i].itemQuantity * menu[j].Price;
                bill += itemSubtotal;

                 // ordered items
                QString itemText = QString("%1 - Code: %2 - Price: Rs.%3 x %4 = $%5")
                    .arg(menu[j].Name)  // Displaying Item 
                    .arg(menu[j].Code)  // Item code
                    .arg(menu[j].Price, 0, 'f', 2)  // Price
                    .arg(order[i].itemQuantity)  // Quantity
                    .arg(itemSubtotal, 0, 'f', 2);  // subtotal
                saveSalesFile(itemText);
                QLabel* itemLabel = new QLabel(itemText, this);
                itemLabel->setStyleSheet("font-size: 10px; font-family: 'American Typewriter'; color: black;");
                layout->addWidget(itemLabel); 
          
                break;
                }
            }
        }
        
         QSpacerItem* beforetaxdisplaySpacer = new QSpacerItem(6, 500);
        layout->addItem(beforetaxdisplaySpacer);

        QLabel* billbefore = new QLabel(QString("total: Rs.%1").arg(bill, 0, 'f', 2), this);
        billbefore->setStyleSheet("font-size: 10px; font-family: 'American Typewriter'; color: black;");
        layout->addWidget(billbefore);
        float tax= TAX*bill;
        QLabel* billLabel = new QLabel(QString("tax is : Rs.%1").arg(tax, 0, 'f', 2), this);
        billLabel->setStyleSheet("font-size: 10px; font-family: 'American Typewriter'; color: black;");
        layout->addWidget(billLabel);

        bill = bill + tax;
        QLabel* taxbillLabel = new QLabel(QString("Your total after is : Rs.%1").arg(bill, 0, 'f', 2), this);
        taxbillLabel->setStyleSheet("font-size: 10px; font-family: 'American Typewriter'; color: black;");
        layout->addWidget(taxbillLabel);
        
        QLabel* voucherLabel = new QLabel("Enter voucher code (Optional):", this);
        voucherLabel->setStyleSheet("font-size: 10px; font-family: 'American Typewriter'; color: black;");
        QLineEdit* voucherInput = new QLineEdit(this);
        voucherInput->setPlaceholderText("Enter voucher code...");
        voucherInput->setStyleSheet("font-size: 10px; font-family: 'American Typewriter'; color: black;background-color: white;");
        layout->addWidget(voucherLabel);
        layout->addWidget(voucherInput);

        QPushButton* applyVoucherButton = new QPushButton("Apply Voucher", this);
        applyVoucherButton->setStyleSheet("font-size: 10px; font-family: 'American Typewriter'; color: black; background-color: white; border-radius: 10px; padding: 5px;");
        layout->addWidget(applyVoucherButton);

        QLabel* finalTotalLabel = new QLabel("", this);
        layout->addWidget(finalTotalLabel);

        connect(applyVoucherButton, &QPushButton::clicked, [this, voucherInput, bill, finalTotalLabel]() {

            QString voucher = voucherInput->text();

            float finalBill = bill;
            bool voucherApplied = false;

            if (voucher == "FIRSTORDER10" || voucher == "ONLINE10" || voucher == "FAMILYFUN") {
                finalBill -= finalBill * 0.1;  // 10% discount for small orders
                voucherApplied = true;
            } else if (voucher == "ONLINE25" && finalBill > 3000) {
                finalBill -= finalBill * 0.25;  // 25% discount for big orders
                voucherApplied = true;
            } else if (voucher == "ONLINE25") {
                finalTotalLabel->setText("Order must be at least $1000 for the ONLINE25 voucher.");
                return;
            }

            // bill after discount
            if (voucherApplied) {
                finalTotalLabel->setText(QString("Your total after voucher is: Rs.%1").arg(finalBill, 0, 'f', 2));
                  finalTotalLabel->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter';");
            } else {
                finalTotalLabel->setText(QString("No voucher applied. Your total is: Rs.%1").arg(finalBill, 0, 'f', 2));
                finalTotalLabel->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter';");
            }
        });

        // back button to go back to the main screen
        QPushButton* backButton = new QPushButton("Back", this);
        backButton->setStyleSheet("font-size: 14px; background-color: white; color: black; font-family: 'American Typewriter';border-radius: 10px; padding: 5px;");
        connect(backButton, &QPushButton::clicked, this, &MyWindow::showInitialLayout);
        layout->addWidget(backButton);
    }



};

int main(int argc, char* argv[]) 
{
    QApplication app(argc, argv);
    MyWindow window;
    window.setGeometry(100, 100, 1170, 584);
    QPalette palette;
    QPixmap background("/Users/sarasafdar/Downloads/hello.jpeg");
    palette.setBrush(window.backgroundRole(), QBrush(background.scaled(window.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    window.setPalette(palette);
    window.setAutoFillBackground(true);
    window.show();
    return app.exec();
}

