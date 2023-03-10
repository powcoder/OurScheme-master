https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#include "Table.hpp"

Table::Table( string tableName, GroupN groupN ) : Table( groupN ) {
  ifstream fin( tableName.c_str(), ifstream::in ) ;

  Token nextToken ;
  nextToken.groupN = groupN ;
  while ( fin >> nextToken.index >> nextToken.name )
    SetToken( nextToken ) ;
}

void Table::SetToken( Token &t ) {
  t.index = m_list.size() + 1 ;
  m_list.push_back( t ) ;
} // SetToken()

void Table::SetIdentifier( Identifier &id ) {
  Hash( id.token ) ;
  if ( id.idtype == MAINPROGRAM ) id.subroutine = id.token.index;
  m_idtable.push_back( id ) ;
}

void Table::SetLABEL( Identifier id ) {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ ) {
    if ( id.token.name == it->token.name &&
         id.subroutine == it->subroutine &&
         LABEL == it->idtype )
      it->pointer = id.pointer ;
  } // for
} //

unsigned int Table::GetMAINPROGRAM() {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ )
    if( it->idtype == MAINPROGRAM ) return it->token.index ;
  return 0 ;
} // GetMAINPROGRAM()

unsigned int Table::GetIDIndex( Token t ) {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ )
    if( t.name == it->token.name ) return it->token.index ;
  return 0 ;
} // GetIDIndex()

bool Table::CmpToken( Token &t ) {
  for ( auto it = m_list.begin() ; it < m_list.end() ; it++ ) {
    if ( t.name == it->name ) {
      t = *it ;
      return true ;
    } // if
  } // for

  return false ;
} // CmpToken()

bool Table::CmpType( Token t, IDType idtype ) {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ ) {
    if ( t.name == it->token.name && idtype == it->idtype )
      return true ;
  } // for

  return false ;
} // CmpType()

bool Table::CmpVariable( Token &t, unsigned int subroutine ) {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ ) {
    if ( t.name == it->token.name && it->subroutine == subroutine &&
         CmpVariableType( *it ) ) {
      t = it->token ;
      return true ;
    } // if
  } // for

  return false ;
} // CmpVariable()

bool Table::CmpLABEL( Identifier &id ) {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ ) {
    if ( id.token.name == it->token.name &&
         id.subroutine == it->subroutine &&
         LABEL == it->idtype ) {
      id.pointer = it->token.index ;
      return true ;
    }  // if
  } // for

  return false ;
} // CmpLABEL()

unsigned int Table::CmpLABEL( unsigned int i ) {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ ) {
    if ( i == it->token.index )
      return it->pointer ;
  } // for

  return 0 ;
} // CmpLABEL()

bool Table::CmpSUBROUTINE( Identifier &id ) {
  for ( auto it = m_idtable.begin() ; it < m_idtable.end() ; it++ ) {
    if ( id.token.name == it->token.name && SUBROUTINEID == it->idtype ) {
      id = *it ;
      return true ;
    }  // if
  } // for

  return false ;
} // CmpSUBROUTINE()

void Table::Hash( Token &t ) {
  t.index = 0 ;
  for ( string::iterator it = t.name.begin() ; it < t.name.end(); it++ )
    t.index += *it ;

  t.index %= 100 ;

  for ( IdentifierTable::iterator it = m_idtable.begin() ; it < m_idtable.end() ; it++ ) {
    if ( t.index == it->token.index ) {
      ++t.index ;
      it = m_idtable.begin() ; // �q�Y�Arun�@��
    } // if
  } // for
} // Hash
