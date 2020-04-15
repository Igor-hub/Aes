#ifndef _AES_HPP
#define _AES_HPP

typedef unsigned char   byte;

class   aes {

#if !defined(AES_128) && !defined(AES_192) && !defined(AES_256)
#define AES_128     
#define AES_192
#define AES_256
#endif

public:
    enum   status   {
        Ok                  = 0,    ///< нет ошибки.
        wrong_key_lenght    = ~0    ///< неверная длина ключа.
    };

    static const unsigned  block_size = 16;

    void
      encrypt(
        const byte      in[block_size], ///< Входной блок данных.
        byte            out[block_size] ///< Выходной блок данных.  @see block_size
        );
    void
      decrypt(
        const byte      in[block_size], ///< Входной блок данных.
        byte            out[block_size] ///< Выходной блок данных. @see block_size
        );
    status
      expand_key(
        const byte    * key,            ///< Ключ.
        const unsigned  size            ///< Размер ключа в битах.
        );
   
protected:
    unsigned    rounds; 
    typedef unsigned long   u32;

    u32     encryption_round_key[64],
            decryption_round_key[64];

    static  u32 s_box[256];     ///< Прямая замена
    static  u32 r_box[256];     ///< Обратная замена
    static  u32 ft[4][256];     ///< Расширенная прямая замена
    static  u32 rt[4][256];     ///< Расширенная обратная замена
    
    void inline
      init_tables();
 
    static const unsigned   basis = 1<<8 | 1<<4 | 1<<3 | 1<<1 | 1<<0;


    byte static inline 
      lfsr2(
        byte    a           ///< Предыдущее состойние генератора.
        );

    u32 static inline 
      rot_left_8( 
        u32 value           ///< Сдвигаемое значение.
        );

    u32 static inline 
      get( 
        const byte array[4] ///< Указатель на массив из 4-х байт.
        );

    void static inline 
      put( 
        u32  value,         ///< Исходные данные.
        byte array[4]       ///< Указатель на массив из четырёх байт. 
        );

    u32 static inline
      fb(
        u32 byte,           ///< Слово содержащее байт.
        unsigned position   ///< Позиция байта в слове.
        );

    u32 static inline
      rb(
        u32 byte,           ///< Слово содержащее байт.
        unsigned position   ///< Позиция байта в слове.
        );

};//class   aes


#endif