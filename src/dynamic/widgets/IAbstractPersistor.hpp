#pragma once

class IAbstractPersistor {
public:
    virtual ~IAbstractPersistor() = default;

    virtual void load() = 0;
    virtual void store() = 0;
};
