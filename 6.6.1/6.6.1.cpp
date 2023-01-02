#include <iostream>

#include <Source.cpp>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

int main()
{
    try {
        std::string connectionString =
            "host=localhost"
            " port=5432"
            " dbname= "
            " user= "
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