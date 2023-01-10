#include <iostream>

#include <Classes.h>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

int main()
{
    try {
        std::string connectionString =
            "host=localhost"
            " port=5432"
            " dbname="
            " user="
            " password=";

        auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);

        Wt::Dbo::Session session;
        session.setConnection(std::move(postgres));
        session.mapClass<Publisher>("Publisher");
        session.mapClass<Book>("Book");
        session.mapClass<Shop>("Shop");
        session.mapClass<Stock>("Stock");
        session.mapClass<Sale>("Sale");

        session.createTables();
        
        Wt::Dbo::Transaction transaction{session};

        std::unique_ptr<Publisher> publishers{ new Publisher() };
        publishers->name = "Star";
        Wt::Dbo::ptr<Publisher> p = session.add(std::move(publishers));
        
        
        std::unique_ptr<Book> books{ new Book() };
        books->title = "Developer in C++";
        Wt::Dbo::ptr<Publisher> name_pub = session.find<Publisher>().where("name = ?").bind("Star");
        books->publisher = name_pub;
        Wt::Dbo::ptr<Book> b = session.add(std::move(books));

        std::unique_ptr<Shop> shops{ new Shop() };
        shops->name = "Read the city";
        Wt::Dbo::ptr<Shop> sh = session.add(std::move(shops));

        
        std::unique_ptr<Stock> stocks{ new Stock() };
        stocks->count = 3;
        Wt::Dbo::ptr<Book> title_book = session.find<Book>().where("title = ?").bind("Developer in C++");
        stocks->book = title_book;
        Wt::Dbo::ptr<Shop> name_shop = session.find<Shop>().where("name = ?").bind("Read the city");
        stocks->shop = name_shop;
        Wt::Dbo::ptr<Stock> st = session.add(std::move(stocks));

        
        std::unique_ptr<Sale> sales{ new Sale() };
        sales->price = 35;
        sales->data_sale = "15.01.2023";
        sales->count = 5;
        Wt::Dbo::ptr<Stock> id_stock = session.find<Stock>().where("id = ?").bind("1");
        sales->stock = id_stock;
        Wt::Dbo::ptr<Sale> sa = session.add(std::move(sales));

        transaction.commit();
    }
    catch (const Wt::Dbo::Exception& e)
    {
        std::cout << "wtdbo Error: " << e.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error : " << ex.what() << std::endl;
    }

    return 0;
}