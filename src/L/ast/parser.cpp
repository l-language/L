#include <L/ast/parser.hpp>
using namespace std;
namespace L{
    namespace AST{
        std::shared_ptr<Node> Parser::operator()(){
	        while((current = lexer()) != Token(Operator::EndOfFile)){
		        cout << current.get() << endl;
                switch(current.type){
                    case TokenKind::Keyword:{
                        return readKeyword();
                    }
                    case TokenKind::Identifier:{
                        return readIdentifier();
                    }
                }
	        }
            return nullptr;
        }
        std::shared_ptr<Node> Parser::readKeyword(){
            switch(current.index){
                case 0: { // let
                    Token name = next();
                    if(name.type != TokenKind::Identifier){
                        return nullptr;
                    }
                    if(next() != Token(Operator::Colon)){
                        return nullptr;
                    }
                    Token type = next();
                    if(type.type != TokenKind::Keyword&&type.type != TokenKind::Identifier){
                        return nullptr;
                    }
                    std::shared_ptr<Node> result(new VariableDeclare(
                        name.index, type, operator()()
                    ));
                    return result;
                }
            }
        }
        std::shared_ptr<Node> Parser::readIdentifier(){
            return nullptr;
        }
    }
}