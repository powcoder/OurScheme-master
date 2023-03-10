https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std ;

enum TokenType {
  LEFTPAREN, RIGHTPAREN,
  INT, FLOAT,
  STRING,
  DOT,
  NIL, T,
  SYMBOL,
  COMMAND,
  NOTHING
};

class LineCounter {
public:
  LineCounter() {
    m_newLine = false ;
    m_line = 1 ;
    m_column = 1 ;
  } // LineCounter::LineCounter()

  void Reset( bool isSkip ) {
    m_newLine = !isSkip ;
    m_line = 1 ;
    m_column = 1 ;
  } // LineCounter::Reset()

  char Counter( const char &ch ) ;

  unsigned int GetLineNum() { return m_line ; } // GetLineNum()

  unsigned int GetColumnNum() { return m_column ; } // GetColumnNum()

  // void SetColumnNum( unsigned int n ) { m_column = n ; } // SetColumnNum()

protected:
private:
  bool m_newLine ;
  unsigned int m_line ;
  unsigned int m_column ;
  unsigned int m_oldline ;
  unsigned int m_oldcolumn ;

};

class Token {
public:
  Token() { m_type = NOTHING ; } // Token()

  Token( LineCounter &lc ) { GetToken( lc ); }
  Token( TokenType type ) ; // Token()

  Token( TokenType type, string str ) ; // Token()

  void Initialization() {
    m_type = NOTHING ;
    m_name = "" ;
  } // Initialization() ;

  void GetToken( LineCounter &lc ) ;


  // set
  void SetType( TokenType type ) { m_type = type ; } // SetType()

  void SetName( string str ) { m_name = str ; } // SetName()

  inline TokenType GetType() { return m_type; }

  inline string GetName() { return m_name; }

  bool GetBool() {
    if ( CheckType( T ) ) return true ;
    else if ( CheckType( NIL ) )  return false ;
    else return true ;
  } // GetBool()

  // Check

  inline bool CheckType( TokenType type ) { return ( m_type == type ) ; }

  inline bool CheckName( string str ) { return ( m_name == str ) ; }

  inline bool CheckToken( Token * token ) { return ( m_name == token->GetName() ) ; }

  bool CheckCommandType() ;

  string Str() ;

protected:
private:
  TokenType m_type ;
  string m_name ;

  char CharPeek( LineCounter &lc ) ;

  bool AnalysisNumToken( string & str ) ;
} ;

typedef Token *TokenP ;
typedef vector<TokenP> TokenPs ;

typedef vector<Token> Tokens ;

#endif // TOKEN_H_INCLUDED
