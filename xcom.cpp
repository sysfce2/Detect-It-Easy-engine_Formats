/* Copyright (c) 2020-2023 hors<horsicq@gmail.com>
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
#include "xcom.h"

XCOM::XCOM(QIODevice *pDevice, bool bIsImage, XADDR nModuleAddress) : XBinary(pDevice, bIsImage, nModuleAddress)
{
    XBinary::setBaseAddress(XCOM_DEF::ADDRESS_BEGIN);
}

XCOM::~XCOM()
{
}

bool XCOM::isValid()
{
    bool bResult = false;

    // mb TODO mb
    if (getSize() < XCOM_DEF::IMAGESIZE) {
        bResult = true;
    }

    return bResult;
}

bool XCOM::isValid(QIODevice *pDevice, bool bIsImage, XADDR nModuleAddress)
{
    XCOM xcom(pDevice, bIsImage, nModuleAddress);

    return xcom.isValid();
}

XBinary::MODE XCOM::getMode(QIODevice *pDevice, bool bIsImage, XADDR nModuleAddress)
{
    XCOM xcom(pDevice, bIsImage, nModuleAddress);

    return xcom.getMode();
}

XBinary::_MEMORY_MAP XCOM::getMemoryMap(PDSTRUCT *pPdStruct)
{
    PDSTRUCT pdStructEmpty = XBinary::createPdStruct();

    if (!pPdStruct) {
        pPdStruct = &pdStructEmpty;
    }

    _MEMORY_MAP result = {};

    qint64 nTotalSize = getSize();

    result.nModuleAddress = getModuleAddress();
    result.nEntryPointAddress = result.nModuleAddress;
    result.nRawSize = nTotalSize;
    result.nImageSize = getImageSize();
    result.fileType = getFileType();
    result.mode = getMode();
    result.sArch = getArch();
    result.bIsBigEndian = isBigEndian();
    result.sType = getTypeAsString();

    qint64 nCodeSize = qMin(nTotalSize, (qint64)(XCOM_DEF::IMAGESIZE - XCOM_DEF::ADDRESS_BEGIN));

    _MEMORY_RECORD record = {};
    record.nAddress = 0;
    record.segment = ADDRESS_SEGMENT_FLAT;
    record.nOffset = -1;
    record.nSize = XCOM_DEF::ADDRESS_BEGIN;
    record.nIndex++;
    record.bIsVirtual = true;

    result.listRecords.append(record);

    _MEMORY_RECORD recordMain = {};
    recordMain.nAddress = XCOM_DEF::ADDRESS_BEGIN;
    recordMain.segment = ADDRESS_SEGMENT_FLAT;
    recordMain.nOffset = 0;
    recordMain.nSize = nCodeSize;
    recordMain.nIndex++;

    result.listRecords.append(recordMain);

    qint64 nVirtualSize = (qint64)(XCOM_DEF::IMAGESIZE - XCOM_DEF::ADDRESS_BEGIN) - nTotalSize;

    if (nVirtualSize > 0) {
        _MEMORY_RECORD record = {};
        record.nAddress = XCOM_DEF::ADDRESS_BEGIN + nCodeSize;
        record.segment = ADDRESS_SEGMENT_FLAT;
        record.nOffset = -1;
        record.nSize = nVirtualSize;
        record.nIndex++;
        record.bIsVirtual = true;

        result.listRecords.append(record);
    }

    if (nTotalSize > nCodeSize) {
        _MEMORY_RECORD recordOverlay = {};
        recordOverlay.nAddress = -1;
        recordOverlay.nOffset = nCodeSize;
        recordOverlay.nSize = nTotalSize - nCodeSize;
        recordOverlay.nIndex++;
        recordOverlay.type = MMT_OVERLAY;

        result.listRecords.append(recordOverlay);
    }

    return result;
}

QString XCOM::getArch()
{
    return QString("8086");
}

XBinary::MODE XCOM::getMode()
{
    return MODE_16;
}

bool XCOM::isBigEndian()
{
    return false;
}

qint64 XCOM::getImageSize()
{
    return 0x10000;
}

XBinary::FT XCOM::getFileType()
{
    return FT_COM;
}

qint32 XCOM::getType()
{
    return TYPE_EXECUTABLE;
}

XBinary::OSINFO XCOM::getOsInfo()
{
    OSINFO result = {};

    result.osName = OSNAME_MSDOS;
    result.sOsVersion = "";  // TODO
    result.sArch = getArch();
    result.mode = getMode();
    result.sType = typeIdToString(getType());
    result.bIsBigEndian = isBigEndian();

    return result;
}

QString XCOM::typeIdToString(qint32 nType)
{
    QString sResult = tr("Unknown");

    switch (nType) {
        case TYPE_UNKNOWN:
            sResult = tr("Unknown");
            break;
        case TYPE_EXECUTABLE:
            sResult = QString("EXE");
            break;
    }

    return sResult;
}
