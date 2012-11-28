#
# Tabela para guardar Usuarios
#

CREATE TABLE  Usuarios (
  
    Login char(10) NOT NULL,

    Nome varchar(15) NOT NULL,

    Sobrenome varchar(30) NOT NULL,

    Senha varchar(16) NOT NULL,

    PRIMARY KEY  (Login)
);
