https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#ifndef TABLE_H
#define TABLE_H

#include <fstream>
#include <vector>

#include "Token.hpp"

enum IDType { MAINPROGRAM = 0, ARRAY = 1, BOOLEAN = 2, /*CHARACTER = 3,*/
              INTEGER = 4, LABEL = 5, REAL = 6,
              SUBROUTINEID = 7, GOTOID = 8, CALLID = 9, ENDID = 10 };

struct Identifier {
  Token token ;
  unsigned int subroutine ;
  IDType idtype ;
  unsigned int pointer ;
} ;

typedef vector<Identifier> IdentifierTable ;
typedef vector<unsigned int> InformationTable ;

typedef int GroupN ;

class Table {
public:
  Table() { m_list.clear() ; }
  // virtual ~Table();

  Table( GroupN groupN ) : Table() { SetTableN( groupN ) ; }

  Table( string tableName, GroupN groupN );

  void SetTableN( GroupN val ) { m_tableN = val; }
  void SetToken( Token &t ) ;
  void SetIdentifier( Identifier &id ) ;
  void SetLABEL( Identifier id ) ;

  auto GetList() { return m_list; }
  auto GetIDTable() { return m_idtable; }
  unsigned int GetMAINPROGRAM() ;
  unsigned int GetIDIndex( Token t ) ;

  bool CmpToken( Token &t ) ;
  // bool CmpIdentifier( token &t ) ;
  bool CmpType( Token t, IDType idtype ) ;
  bool CmpVariableType( Identifier id ) {
    return ( id.idtype == ARRAY || id.idtype == BOOLEAN ||
             id.idtype == INTEGER || id.idtype == REAL ) ; }
  bool CmpVariable( Token &t, unsigned int subroutine ) ;
  bool CmpLABEL( Identifier &id ) ;
  unsigned int CmpLABEL( unsigned int i ) ;
  bool CmpSUBROUTINE( Identifier &id ) ;

  void Hash( Token &t ) ;

protected:
private:
  GroupN m_tableN ;
  Tokens m_list ;
  IdentifierTable m_idtable ;
} ;

#endif // TABLE_H
