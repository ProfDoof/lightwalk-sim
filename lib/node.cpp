#include "effect.h"

class Node
{
  public:
    /**
    * id: id of this node
    * offset: x offset of this node, from 0 - 1000?
    * e: an effect
    * length: if > 0, then it's the same for each reed, else use lengths[]
    * lengths: if length <1, then use this array for individual reed lengths
    */
    Node(int id, int offset, Effect *e, int length, int lengths[REED_COUNT])
    {
        if (length <= 1) {
            for (int i=0; i< REED_COUNT; i++) {
                _reedLength[i] = lengths[i];
            }
         } else {
            _allReedsLength = length;
        }
        _e = e;
        _e->set_xOffset( offset );
        _offset = offset;
    }

    ~Node() {}
    
    Effect * effect () { return _e; }
    int offset () { return _offset; }

    int reedLengthAt(int i) {
        if (_allReedsLength > 0)
        return _allReedsLength;

        return _reedLength[i];
    }

  private:
    Effect * _e;
    int _allReedsLength= 0;
    int _reedLength[REED_COUNT];
    int _offset = -1;
};
