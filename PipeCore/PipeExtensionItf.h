

enum ProviderTye {
    ProviderTypeStorage,
    ProviderTypeService,
    ProviderTypeGateway
};

class IProvider {
    ProviderTye getType() = 0;
};

class IProviderService : IProvider {

};

class IProviderGateway : IProvider {

};

class IProviderStorage : IProvider {
    
};