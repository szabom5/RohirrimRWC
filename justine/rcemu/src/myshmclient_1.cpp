/**
 * @brief Justine - this is a rapid prototype for development of Robocar City Emulator
 *
 * @file myshmclient.cpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.10
 *
 * @section LICENSE
 *
 * Copyright (C) 2014 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * Robocar City Emulator and Robocar World Championship
 *
 * desc
 *
 */

#include <myshmclient.hpp>
//#include <trafficlexer.hpp>


char data[524288];


		
std::vector<justine::sampleclient::MyShmClient::Gangster> justine::sampleclient::MyShmClient::gangsters ( boost::asio::ip::tcp::socket & socket, int id,
    osmium::unsigned_object_id_type cop )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<gangsters " );
  length += std::sprintf ( data+length, "%d>", id );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );
    }

  /* reading all gangsters into a vector */
  int idd {0};
  unsigned f, t, s;
  int n {0};
  int nn {0};
  std::vector<Gangster> gangsters;
 std::cout<<std::endl<<data<<std::endl<<std::endl<<std::endl;
  while ( std::sscanf ( data+nn, "<OK %d %u %u %u>%n", &idd, &f, &t, &s, &n ) == 4 )
    {
      nn += n;
      gangsters.push_back ( Gangster {idd, f, t, s} );
    }

  std::sort ( gangsters.begin(), gangsters.end(), [this, cop] ( Gangster x, Gangster y )
  {
    return dst ( cop, x.to ) < dst ( cop, y.to );
  } );

 // std::cout.write ( data, length );
 // std::cout << "Command GANGSTER sent." << std::endl;

  return gangsters;
}
		//initcops
std::vector<justine::sampleclient::MyShmClient::Cop> justine::sampleclient::MyShmClient::initcops ( boost::asio::ip::tcp::socket & socket )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<init guided %s 10 c>", m_teamname.c_str() ); //cop számát változtatni lehet

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );


  if ( err == boost::asio::error::eof )
    {
				
      // TODO vége lett a kapcsolatnak.

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );
    }

  /* reading all cops into a vector */
  int idd {0};
  int f, t;
  char c;
  int n {0};
  int nn {0};
  std::vector<Cop> cops;

  while ( std::sscanf ( data+nn, "<OK %d %d/%d %c>%n", &idd, &f, &t, &c, &n ) == 4 )
    {
      nn += n;
      cops.push_back ( idd );
    }

  //std::cout.write ( data, length );
 // std::cout << "Command INIT sent." << std::endl;

  return cops;
}


int justine::sampleclient::MyShmClient::init ( boost::asio::ip::tcp::socket & socket ) //init
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<init guided %s 1 c>", m_teamname.c_str() );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );

    }

  int id {0};
  std::sscanf ( data, "<OK %d", &id );

  //std::cout.write ( data, length );
 // std::cout << "Command INIT sent." << std::endl;

  return id;

}

void justine::sampleclient::MyShmClient::pos ( boost::asio::ip::tcp::socket & socket, int id ) //pos
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<pos " );
  length += std::sprintf ( data+length, "%d %u %u>", id, 2969934868u, 651365957u );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );

    }

  //std::cout.write ( data, length );
 // std::cout << "Command POS sent." << std::endl;
}

			//car
void justine::sampleclient::MyShmClient::car ( boost::asio::ip::tcp::socket & socket, int id, unsigned *f, unsigned *t, unsigned* s )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<car " );
  length += std::sprintf ( data+length, "%d>", id );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );
    }

  int idd {0};
  std::sscanf ( data, "<OK %d %u %u %u", &idd, f, t, s );

 // std::cout.write ( data, length );
 // std::cout << "Command CAR sent." << std::endl;

}

void justine::sampleclient::MyShmClient::route (				//route
  boost::asio::ip::tcp::socket & socket,
  int id,
  std::vector<osmium::unsigned_object_id_type> & path
)
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data,
                                 "<route %d %d", path.size(), id );

  for ( auto ui: path )
    length += std::sprintf ( data+length, " %u", ui );

  length += std::sprintf ( data+length, ">" );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );

    }

  //std::cout.write ( data, length );
 // std::cout << "Command ROUTE sent." << std::endl;

}

void justine::sampleclient::MyShmClient::start ( boost::asio::io_service& io_service, const char * port )
{

#ifdef DEBUG
  foo();
#endif

  boost::asio::ip::tcp::resolver resolver ( io_service );
  boost::asio::ip::tcp::resolver::query query ( boost::asio::ip::tcp::v4(), "localhost", port );
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve ( query );

  boost::asio::ip::tcp::socket socket ( io_service );
  boost::asio::connect ( socket, iterator );

  int id = init ( socket );

  pos ( socket, id );

  unsigned int g {0u};
  unsigned int f {0u};
  unsigned int t {0u};
  unsigned int s {0u};

  std::vector<Gangster> gngstrs;

  for ( ;; )
    {
      std::this_thread::sleep_for ( std::chrono::milliseconds ( 200 ) );

      car ( socket, id, &f, &t, &s );

      gngstrs = gangsters ( socket, id, t );

      if ( gngstrs.size() > 0 )
        g = gngstrs[0].to;							
      else
        g = 0;
      if ( g > 0 )
        {

          std::vector<osmium::unsigned_object_id_type> path = hasDijkstraPath ( t, g );

          if ( path.size() > 1 )
            {

              std::copy ( path.begin(), path.end(),
                          std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );

              route ( socket, id, path );
            }
        }
    }
}

/*********************************************/
//	azonos gegszterre ne menjen több rendőr
/*********************************************/

void justine::sampleclient::MyShmClient::start10 ( boost::asio::io_service& io_service, const char * port )
{

#ifdef DEBUG
  foo();
#endif

  boost::asio::ip::tcp::resolver resolver ( io_service );
  boost::asio::ip::tcp::resolver::query query ( boost::asio::ip::tcp::v4(), "localhost", port );
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve ( query );

  boost::asio::ip::tcp::socket socket ( io_service );
  boost::asio::connect ( socket, iterator );

  std::vector<Cop> cops = initcops ( socket );

  unsigned int g {0u};
  unsigned int f {0u};
  unsigned int t {0u};
  unsigned int s {0u};

  std::vector<Gangster> gngstrs;
  
  //új változók: count{a foglalt vector nullázására}, xyz segédváltozó
  int count, xyz=0;
  // gengszter azonosítására szolgál, nem id, hanem a to-ból
  typedef int Gid;
 	//segéd pair változó a foglalt vector feltöltéshez
 	std::pair<Gid,Cop> asd;
 	
 	
  for ( ;; )
    {
      std::this_thread::sleep_for ( std::chrono::milliseconds ( 200 ) ); 
      // a foglalt vectorban tároljuk minden egyes gengszterhez a rendőrök kiosztását
			std::vector<std::pair<Gid,Cop>> foglalt;
			count=0;
      for ( auto cop:cops )
        {
          car ( socket, cop, &f, &t, &s );
          
          gngstrs = gangsters ( socket, cop, t );			//eredeti, 1 gngstrs vector/cop
          //új ciklus, amely a kezdeti állapotban nullázza, azaz felszabadítsa a gengszterek beosztását
          for(int i=0;i<gngstrs.size();i++)
	          if(!count && gngstrs.size()>0)
				      		{
				      				for(int i=0;i<gngstrs.size();i++)
											{
												asd.first=gngstrs[i].to;
												asd.second=0;
												foglalt.push_back(asd);
											}          
											count++;
									}
					
					
					//a rendőrök küldése a megfelelő gengszterre,
					//kiegészítés, vizsgálat, hogy arra a gengszterre nem-e ment már előzőleg rendőr, akkor xyz-vel a következő legközelebbire megy
					if ( gngstrs.size() > 0 )
					{	
					xyz=0;
					g=0;
						for(int i=0;i<foglalt.size();i++)
						{  
								if(foglalt[i].first==(gngstrs[xyz].to) && foglalt[i].second==0)
								{
									g = gngstrs[xyz].to;
									foglalt[i].second=cop;
									
									
									break;		
								}else if(foglalt[i].first==(gngstrs[xyz].to) && foglalt[i].second!=0 )
									{xyz++; i=-1; }// ekkor lépteti tovább, a következő legközelebbire
									
						}//ha már "elfogytak a szabad gengszterek, akkor se tétlenkedjenek"
						if(g==0)//nem talalt egyetlen ures gangstert sem
						   g=gngstrs[0].to;//akkor menjen a legkozelebbire
					}
					else
						g = 0;
	
						
						if ( g > 0 )
						  {
						  
								std::vector<osmium::unsigned_object_id_type> path=hasDijkstraPath ( t, g );
								
						   if ( path.size() >= 0 )
						      {

						        std::copy ( path.begin(), path.end(),
						                    std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );
	
										route ( socket, cop, path ); 
						      }
						  }
						 
        }
    }
}
