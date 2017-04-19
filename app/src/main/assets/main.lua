require 'torchandroid'
require 'torch'
require 'nn'

torch.setdefaulttensortype('torch.FloatTensor')
model = nil;

function init(netPath)
    print('Load net from dynamic path')
    model=torch.load(netPath,'ascii')
    print('Net loaded successfully')
end

function call(tensor)
    local result = model:forward(tensor)
    -- Since my net is only an empty stub I won't return the actual result but just a mock value
    return 1
end
