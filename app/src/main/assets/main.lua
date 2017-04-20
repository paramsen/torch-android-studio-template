require 'torchandroid'
require 'torch'
require 'nn'

torch.setdefaulttensortype('torch.FloatTensor')
model = nil;

function init(netPath)
    print('Load net from dynamic path')
    -- I don't actually have a working net to ship, so this is commented out
    -- model=torch.load(netPath,'ascii')
    print('Net loaded successfully')
end

function call(tensor)
    -- Since my net is only an empty stub I won't return the actual result but just a mock value
    -- local result = model:forward(tensor)
    return 1
end
