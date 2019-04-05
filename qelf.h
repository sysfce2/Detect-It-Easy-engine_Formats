// copyright (c) 2017-2019 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef QELF_H
#define QELF_H

#include "qbinary.h"
#include "qelf_def.h"

// TODO buffer big Endian();
class QELF : public QBinary
{
    Q_OBJECT
    struct NOTE
    {
        quint16 type;
        QString name;
        QByteArray desc;
    };

public:
    QELF(QIODevice *__pDevice=nullptr,bool bIsImage=false,qint64 nImageAddress=-1);
    ~QELF();

    virtual bool bIsValid();
    bool isBigEndian();
    bool is64();

    quint32 getIdent_Magic();
    void setIdent_Magic(quint32 value);

    quint8 getIdent_mag(int nMag);
    void setIdent_mag(quint8 value,int nMag);

    quint8 getIdent_class();
    void setIdent_class(quint8 value);
    quint8 getIdent_data();
    void setIdent_data(quint8 value);
    quint8 getIdent_version();
    void setIdent_version(quint8 value);

    quint8 getIdent_osabi();
    void setIdent_osabi(quint8 value);
    quint8 getIdent_abiversion();
    void setIdent_abiversion(quint8 value);

    quint8 getIdent_pad(int nPad);
    void setIdent_pad(quint8 value,int nPad);

    // TODO Hdr32 getHdr32();
    quint16 getHdr32_type();
    void setHdr32_type(quint16 value);
    quint16 getHdr32_machine();
    void setHdr32_machine(quint16 value);
    quint32 getHdr32_version();
    void setHdr32_version(quint32 value);
    quint32 getHdr32_entry();
    void setHdr32_entry(quint32 value);
    quint32 getHdr32_phoff();
    void setHdr32_phoff(quint32 value);
    quint32 getHdr32_shoff();
    void setHdr32_shoff(quint32 value);
    quint32 getHdr32_flags();
    void setHdr32_flags(quint32 value);
    quint16 getHdr32_ehsize();
    void setHdr32_ehsize(quint16 value);
    quint16 getHdr32_phentsize();
    void setHdr32_phentsize(quint16 value);
    quint16 getHdr32_phnum();
    void setHdr32_phnum(quint16 value);
    quint16 getHdr32_shentsize();
    void setHdr32_shentsize(quint16 value);
    quint16 getHdr32_shnum();
    void setHdr32_shnum(quint16 value);
    quint16 getHdr32_shstrndx();
    void setHdr32_shstrndx(quint16 value);

    quint16 getHdr64_type();
    void setHdr64_type(quint16 value);
    quint16 getHdr64_machine();
    void setHdr64_machine(quint16 value);
    quint32 getHdr64_version();
    void setHdr64_version(quint32 value);
    quint64 getHdr64_entry();
    void setHdr64_entry(quint64 value);
    quint64 getHdr64_phoff();
    void setHdr64_phoff(quint64 value);
    quint64 getHdr64_shoff();
    void setHdr64_shoff(quint64 value);
    quint32 getHdr64_flags();
    void setHdr64_flags(quint32 value);
    quint16 getHdr64_ehsize();
    void setHdr64_ehsize(quint16 value);
    quint16 getHdr64_phentsize();
    void setHdr64_phentsize(quint16 value);
    quint16 getHdr64_phnum();
    void setHdr64_phnum(quint16 value);
    quint16 getHdr64_shentsize();
    void setHdr64_shentsize(quint16 value);
    quint16 getHdr64_shnum();
    void setHdr64_shnum(quint16 value);
    quint16 getHdr64_shstrndx();
    void setHdr64_shstrndx(quint16 value);



    static QMap<quint64,QString> getHeaderVersionList();

    static QMap<quint64,QString> getIndentClasses();
    static QMap<quint64,QString> getIndentClassesS();
    static QMap<quint64,QString> getIndentDatas();
    static QMap<quint64,QString> getIndentDatasS();
    static QMap<quint64,QString> getIndentVersions();
    static QMap<quint64,QString> getIndentVersionsS();
    static QMap<quint64,QString> getIndentOsabis();
    static QMap<quint64,QString> getIndentOsabisS();

    static QMap<quint64,QString> getTypes();
    static QMap<quint64,QString> getTypesS();
    static QMap<quint64,QString> getMachines();
    static QMap<quint64,QString> getMachinesS();

    static QMap<quint64,QString> getSectionTypeList();
    static QMap<quint64,QString> getSectionFlagList();

    static QMap<quint64,QString> getProgramTypeList();
    static QMap<quint64,QString> getProgramFlagList();

    QMap<quint32,QString> getStringList(quint32 nSection);
    QString getStringFromList(quint32 nIndex,quint32 nSection);
    QMap<quint32,QString> getStringListMain();
    QString getStringFromListMain(quint32 nIndex);
    QByteArray getSection(quint32 nIndex);
    bool isSectionValid(quint32 nIndex);

    QList<S_Elf32_Shdr> getElf32_ShdrList();
    QList<S_Elf64_Shdr> getElf64_ShdrList();

    S_Elf32_Shdr getElf32_Shdr(quint32 nIndex);
    S_Elf64_Shdr getElf64_Shdr(quint32 nIndex);
    // TODO Set

    quint32 getElf32_Shdr_name(quint32 nIndex);
    quint32 getElf32_Shdr_type(quint32 nIndex);
    quint32 getElf32_Shdr_flags(quint32 nIndex);
    quint32 getElf32_Shdr_addr(quint32 nIndex);
    quint32 getElf32_Shdr_offset(quint32 nIndex);
    quint32 getElf32_Shdr_size(quint32 nIndex);
    quint32 getElf32_Shdr_link(quint32 nIndex);
    quint32 getElf32_Shdr_info(quint32 nIndex);
    quint32 getElf32_Shdr_addralign(quint32 nIndex);
    quint32 getElf32_Shdr_entsize(quint32 nIndex);

    void setElf32_Shdr_name(quint32 nIndex,quint32 value);
    void setElf32_Shdr_type(quint32 nIndex,quint32 value);
    void setElf32_Shdr_flags(quint32 nIndex,quint32 value);
    void setElf32_Shdr_addr(quint32 nIndex,quint32 value);
    void setElf32_Shdr_offset(quint32 nIndex,quint32 value);
    void setElf32_Shdr_size(quint32 nIndex,quint32 value);
    void setElf32_Shdr_link(quint32 nIndex,quint32 value);
    void setElf32_Shdr_info(quint32 nIndex,quint32 value);
    void setElf32_Shdr_addralign(quint32 nIndex,quint32 value);
    void setElf32_Shdr_entsize(quint32 nIndex,quint32 value);

    quint32 getElf64_Shdr_name(quint32 nIndex);
    quint32 getElf64_Shdr_type(quint32 nIndex);
    quint64 getElf64_Shdr_flags(quint32 nIndex);
    quint64 getElf64_Shdr_addr(quint32 nIndex);
    quint64 getElf64_Shdr_offset(quint32 nIndex);
    quint64 getElf64_Shdr_size(quint32 nIndex);
    quint32 getElf64_Shdr_link(quint32 nIndex);
    quint32 getElf64_Shdr_info(quint32 nIndex);
    quint64 getElf64_Shdr_addralign(quint32 nIndex);
    quint64 getElf64_Shdr_entsize(quint32 nIndex);

    void setElf64_Shdr_name(quint32 nIndex,quint32 value);
    void setElf64_Shdr_type(quint32 nIndex,quint32 value);
    void setElf64_Shdr_flags(quint32 nIndex,quint64 value);
    void setElf64_Shdr_addr(quint32 nIndex,quint64 value);
    void setElf64_Shdr_offset(quint32 nIndex,quint64 value);
    void setElf64_Shdr_size(quint32 nIndex,quint64 value);
    void setElf64_Shdr_link(quint32 nIndex,quint32 value);
    void setElf64_Shdr_info(quint32 nIndex,quint32 value);
    void setElf64_Shdr_addralign(quint32 nIndex,quint64 value);
    void setElf64_Shdr_entsize(quint32 nIndex,quint64 value);

    QList<S_Elf32_Phdr> getElf32_PhdrList();
    QList<S_Elf64_Phdr> getElf64_PhdrList();

    S_Elf32_Phdr getElf32_Phdr(quint32 nIndex);
    S_Elf64_Phdr getElf64_Phdr(quint32 nIndex);

    quint32 getElf32_Phdr_type(quint32 nIndex);
    quint32 getElf32_Phdr_offset(quint32 nIndex);
    quint32 getElf32_Phdr_vaddr(quint32 nIndex);
    quint32 getElf32_Phdr_paddr(quint32 nIndex);
    quint32 getElf32_Phdr_filesz(quint32 nIndex);
    quint32 getElf32_Phdr_memsz(quint32 nIndex);
    quint32 getElf32_Phdr_flags(quint32 nIndex);
    quint32 getElf32_Phdr_align(quint32 nIndex);

    void setElf32_Phdr_type(quint32 nIndex,quint32 value);
    void setElf32_Phdr_offset(quint32 nIndex,quint32 value);
    void setElf32_Phdr_vaddr(quint32 nIndex,quint32 value);
    void setElf32_Phdr_paddr(quint32 nIndex,quint32 value);
    void setElf32_Phdr_filesz(quint32 nIndex,quint32 value);
    void setElf32_Phdr_memsz(quint32 nIndex,quint32 value);
    void setElf32_Phdr_flags(quint32 nIndex,quint32 value);
    void setElf32_Phdr_align(quint32 nIndex,quint32 value);

    quint32 getElf64_Phdr_type(quint32 nIndex);
    quint64 getElf64_Phdr_offset(quint32 nIndex);
    quint64 getElf64_Phdr_vaddr(quint32 nIndex);
    quint64 getElf64_Phdr_paddr(quint32 nIndex);
    quint64 getElf64_Phdr_filesz(quint32 nIndex);
    quint64 getElf64_Phdr_memsz(quint32 nIndex);
    quint32 getElf64_Phdr_flags(quint32 nIndex);
    quint64 getElf64_Phdr_align(quint32 nIndex);

    void setElf64_Phdr_type(quint32 nIndex,quint32 value);
    void setElf64_Phdr_offset(quint32 nIndex,quint64 value);
    void setElf64_Phdr_vaddr(quint32 nIndex,quint64 value);
    void setElf64_Phdr_paddr(quint32 nIndex,quint64 value);
    void setElf64_Phdr_filesz(quint32 nIndex,quint64 value);
    void setElf64_Phdr_memsz(quint32 nIndex,quint64 value);
    void setElf64_Phdr_flags(quint32 nIndex,quint32 value);
    void setElf64_Phdr_align(quint32 nIndex,quint64 value);

    int getSectionIndexByName(QString sName);
    QByteArray getSectionByName(QString sName);

    QString getProgramInterpreterName();
    QString getCommentString();
    QString getCompatibleKernelVersion();

    static NOTE getNote(QByteArray &baData,bool bIsBigEndian);

    virtual QList<MEMORY_MAP> getMemoryMapList();
    virtual qint64 getEntryPointOffset();
};

#endif // QELF_H
