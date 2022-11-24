/* Copyright (c) 2017-2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef XMSDOS_H
#define XMSDOS_H

#include "xbinary.h"
#include "xmsdos_def.h"

class XMSDOS : public XBinary {
    Q_OBJECT

public:
    struct MS_RICH_RECORD  // For PE and LE
    {
        quint16 nId;
        quint16 nVersion;
        quint32 nCount;
    };

    enum TYPE {
        TYPE_UNKNOWN = 0,
        TYPE_EXE
        // TODO EXTENDER?
    };

    explicit XMSDOS(QIODevice *pDevice = nullptr, bool bIsImage = false, XADDR nModuleAddress = -1);
    virtual bool isValid();
    static bool isValid(QIODevice *pDevice, bool bIsImage = false, XADDR nModuleAddress = -1);
    static MODE getMode(QIODevice *pDevice, bool bIsImage = false, XADDR nModuleAddress = -1);

    quint16 get_magic();
    qint32 get_lfanew();

    qint64 getDosHeaderOffset();
    qint64 getDosHeaderSize();
    qint64 getDosHeaderExOffset();
    qint64 getDosHeaderExSize();

    XMSDOS_DEF::IMAGE_DOS_HEADER getDosHeader();
    XMSDOS_DEF::IMAGE_DOS_HEADEREX getDosHeaderEx();
    void setDosHeader(XMSDOS_DEF::IMAGE_DOS_HEADER *pDosHeader);
    void setDosHeaderEx(XMSDOS_DEF::IMAGE_DOS_HEADEREX *pDosHeaderEx);

    void set_e_magic(quint16 nValue);
    void set_e_cblp(quint16 nValue);
    void set_e_cp(quint16 nValue);
    void set_e_crlc(quint16 nValue);
    void set_e_cparhdr(quint16 nValue);
    void set_e_minalloc(quint16 nValue);
    void set_e_maxalloc(quint16 nValue);
    void set_e_ss(quint16 nValue);
    void set_e_sp(quint16 nValue);
    void set_e_csum(quint16 nValue);
    void set_e_ip(quint16 nValue);
    void set_e_cs(quint16 nValue);
    void set_e_lfarlc(quint16 nValue);
    void set_e_ovno(quint16 nValue);
    void set_e_res(qint32 nPosition, quint16 nValue);
    void set_e_oemid(quint16 nValue);
    void set_e_oeminfo(quint16 nValue);
    void set_e_res2(qint32 nPosition, quint16 nValue);
    void set_e_lfanew(quint32 nValue);

    quint16 get_e_magic();
    quint16 get_e_cblp();
    quint16 get_e_cp();
    quint16 get_e_crlc();
    quint16 get_e_cparhdr();
    quint16 get_e_minalloc();
    quint16 get_e_maxalloc();
    quint16 get_e_ss();
    quint16 get_e_sp();
    quint16 get_e_csum();
    quint16 get_e_ip();
    quint16 get_e_cs();
    quint16 get_e_lfarlc();
    quint16 get_e_ovno();
    quint16 get_e_res(qint32 nPosition);
    quint16 get_e_oemid();
    quint16 get_e_oeminfo();
    quint16 get_e_res2(qint32 nPosition);
    quint32 get_e_lfanew();

    virtual _MEMORY_MAP getMemoryMap();

    virtual qint64 getImageSize();
    qint64 getModuleAddress();

    static QMap<quint64, QString> getImageMagics();
    static QMap<quint64, QString> getImageMagicsS();

    bool isLE();
    bool isLX();
    bool isNE();
    bool isPE();

    // rich for PE and LE
    bool isRichSignaturePresent();
    QList<XMSDOS::MS_RICH_RECORD> getRichSignatureRecords();
    qint32 getNumberOfRichIDs();
    qint32 getNumberOfRichIDs(QList<MS_RICH_RECORD> *pListRichSignatureRecords);
    bool isRichVersionPresent(quint32 nVersion);
    bool isRichVersionPresent(quint32 nVersion, QList<MS_RICH_RECORD> *pListRichSignatureRecords);

    // dos stub for LE, NE and PE
    qint64 getDosStubSize();
    qint64 getDosStubOffset();
    QByteArray getDosStub();
    bool isDosStubPresent();
    bool removeDosStub();
    bool addDosStub(QString sFileName);

    virtual MODE getMode();
    virtual QString getArch();
    virtual bool isBigEndian();
    virtual FT getFileType();
    virtual qint32 getType();
    virtual OSINFO getOsInfo();
    virtual QString typeIdToString(qint32 nType);
};

#endif  // XMSDOS_H
